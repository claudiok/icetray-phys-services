/**
 *  $Id$
 *  
 *  Copyright (C) 2011
 *  Nathan Whitehorn <nwhitehorn@icecube.wisc.edu>
 *  and the IceCube Collaboration <http://www.icecube.wisc.edu>
 *  
 */

#include <icetray/I3Module.h>
#include <icetray/I3Units.h>
#include <dataclasses/geometry/I3Geometry.h>
#include <dataclasses/calibration/I3Calibration.h>
#include <dataclasses/status/I3DetectorStatus.h>
#include <dataclasses/I3DOMFunctions.h>

class I3GCDAuditor : public I3Module
{
	public:
		I3GCDAuditor(const I3Context& context);
		void Configure();
		void DetectorStatus(I3FramePtr frame);
	private:
		bool CheckDOM(OMKey om, const I3OMGeo &omgeo,
		    const I3DOMCalibration &cal, const I3DOMStatus &status);
		std::string bad_dom_list_;
		bool AMANDA_is_error_;
};

I3_MODULE(I3GCDAuditor);

I3GCDAuditor::I3GCDAuditor(const I3Context& context) : I3Module(context)
{
	AddParameter("BadDOMList", "List of DOMs not to check", "BadDomsList");
	AddParameter("AMANDAIsAnError", "Fail if geometry contains TWR OMs",
	    true);
	AddOutBox("OutBox");
}

void
I3GCDAuditor::Configure()
{
	GetParameter("BadDOMList", bad_dom_list_);
	GetParameter("AMANDAIsAnError", AMANDA_is_error_);
}

void
I3GCDAuditor::DetectorStatus(I3FramePtr frame)
{
	const I3Vector<OMKey> &bdl = frame->Get<const I3Vector<OMKey> >(
	    bad_dom_list_);
	const I3Geometry &geo = frame->Get<I3Geometry>();
	const I3Calibration &calib = frame->Get<I3Calibration>();
	const I3DetectorStatus &status = frame->Get<I3DetectorStatus>();

	bool err = false;

	for (I3OMGeoMap::const_iterator i = geo.omgeo.begin();
	   i != geo.omgeo.end(); i++) {
		if (std::find(bdl.begin(), bdl.end(), i->first) != bdl.end())
			continue;

		#define bad_dom(...) { log_error(__VA_ARGS__); err = true; \
		    continue; }

		// Check for AMANDA OMs, skipping if they are not an error
		if (i->second.omtype == I3OMGeo::AMANDA && AMANDA_is_error_)
			bad_dom("Geometry contains AMANDA OM%s",
			    i->first.str().c_str());
		if (i->second.omtype == I3OMGeo::AMANDA)
			continue;

		if (calib.domCal.find(i->first) == calib.domCal.end())
			bad_dom("OM%s has no calibration",
			    i->first.str().c_str());
		if (status.domStatus.find(i->first) == status.domStatus.end())
			bad_dom("OM%s has no detector status",
			    i->first.str().c_str());

		#undef bad_dom

		if (!CheckDOM(i->first, i->second,
		    calib.domCal.find(i->first)->second,
		    status.domStatus.find(i->first)->second))
			err = true;
	}

	if (err)
		log_fatal("Errors in GCD information. Check above for "
		    "details.");

	PushFrame(frame);
}

bool I3GCDAuditor::CheckDOM(OMKey om, const I3OMGeo &omgeo,
    const I3DOMCalibration &cal, const I3DOMStatus &status)
{
	#define bad_dom(...) { log_error(__VA_ARGS__); return false; }

	// Check geometry
	if (!std::isfinite(omgeo.position.GetX()) ||
	    !std::isfinite(omgeo.position.GetY()) ||
	    !std::isfinite(omgeo.position.GetZ()))
		bad_dom("OM%s has invalid position", om.str().c_str());

	// Check calibration
	for (int chip = 0; chip < 2; chip++)
	    for (int chan = 0; chan < 3; chan++)
		if (!std::isfinite(cal.GetATWDBeaconBaseline(chip, chan)))
			bad_dom("Invalid baselines for OM%s ATWD chip %d, "
			    "channel %d", om.str().c_str(), chip, chan);
	if (!std::isfinite(cal.GetFADCBeaconBaseline()))
		bad_dom("Invalid baselines for OM%s FADC", om.str().c_str());

	for (int chan = 0; chan < 3; chan++)
		if (!std::isfinite(cal.GetATWDGain(chan)) ||
		    cal.GetATWDGain(chan) >= 0)
			bad_dom("Invalid ATWD gain for OM%s channel %d (%e)",
			    om.str().c_str(), chan, cal.GetATWDGain(chan));
	if (!std::isfinite(cal.GetFADCGain()) || cal.GetFADCGain() <= 0)
		bad_dom("Invalid FADC gain for OM%s (%e)", om.str().c_str(),
		    cal.GetFADCGain());
	for (int chip = 0; chip < 2; chip++)
	    for (int chan = 0; chan < 3; chan++)
		for (int bin = 0; bin < 128; bin++) {
			if (!std::isfinite(cal.GetATWDBinCalibFit(chip, chan,
			    bin).slope) ||
			    cal.GetATWDBinCalibFit(chip, chan, bin).slope >= 0)
				bad_dom("Invalid bin calibration for OM%s "
				    "ATWD chip %d, channel %d, bin %d (%e)",
				    om.str().c_str(), chip, chan, bin,
				    cal.GetATWDBinCalibFit(chip, chan,
				    bin).slope);
	}

	if (!std::isfinite(cal.GetRelativeDomEff()))
		bad_dom("Invalid DOM efficiency for OM%s", om.str().c_str());
	
	if (!std::isfinite(cal.GetDomNoiseRate()) || cal.GetDomNoiseRate() <= 0
	    || cal.GetDomNoiseRate() > 10000*I3Units::hertz)
		bad_dom("Invalid noise rate for OM%s (%f Hz)",
		    om.str().c_str(), cal.GetDomNoiseRate()/I3Units::hertz);

	if (!std::isfinite(cal.GetFrontEndImpedance()) ||
	    cal.GetFrontEndImpedance() <= 0 ||
	    cal.GetFrontEndImpedance() > 100*I3Units::ohm)
		bad_dom("Invalid front end impedance for OM%s (%f Ohm)",
		    om.str().c_str(), cal.GetFrontEndImpedance()/I3Units::ohm);
	if (!std::isfinite(cal.GetATWDResponseWidth()) ||
	    cal.GetATWDResponseWidth() <= 0 || cal.GetATWDResponseWidth() > 1)
		bad_dom("Invalid ATWD response width for OM%s (%f ns)",
		    om.str().c_str(), cal.GetATWDResponseWidth()/I3Units::ns);

	// Check Detector Status
	if (!std::isfinite(status.pmtHV) || status.pmtHV < 100.*I3Units::V ||
	    status.pmtHV > 2000.*I3Units::V)
		bad_dom("Invalid PMT high voltage for OM%s (%f V)",
		    om.str().c_str(), status.pmtHV/I3Units::V);
	
	// Check composite quantities
	if (!std::isfinite(SPEMean(status, cal)) || SPEMean(status, cal) <= 0)
		bad_dom("Invalid mean SPE charge for OM%s (%f pC)",
		    om.str().c_str(), SPEMean(status, cal)/I3Units::pC);
	if (!std::isfinite(TransitTime(status, cal)) ||
	    TransitTime(status, cal) <= 0 ||
	    TransitTime(status, cal) > 200*I3Units::ns)
		bad_dom("Invalid transit time for OM%s (%f ns)",
		    om.str().c_str(), TransitTime(status, cal)/I3Units::ns);
	if (!std::isfinite(PMTGain(status, cal)) || PMTGain(status, cal) <= 0 ||
	    PMTGain(status, cal) > 5e7)
		bad_dom("Invalid PMT gain for OM%s (%e)",
		    om.str().c_str(), PMTGain(status, cal));
	for (int chip = 0; chip < 2; chip++) {
		if (!std::isfinite(ATWDSamplingRate(chip, status, cal)) || 
		    ATWDSamplingRate(chip, status, cal) <= 0 ||
		    ATWDSamplingRate(chip, status, cal) >
		    400*I3Units::megahertz) {
			bad_dom("Invalid ATWD sampling rate for OM%s chip %d "
			    "(%f MHz)", om.str().c_str(), ATWDSamplingRate(
			    chip, status, cal)/I3Units::megahertz);
		}
	}
	if (!std::isfinite(SPEPMTThreshold(status, cal)) ||
	    SPEPMTThreshold(status, cal) <= 0)
		bad_dom("Invalid SPE threshold for OM%s (%f mV)",
		    om.str().c_str(), SPEPMTThreshold(status, cal)/I3Units::mV);

	return true;

	#undef bad_dom
}

