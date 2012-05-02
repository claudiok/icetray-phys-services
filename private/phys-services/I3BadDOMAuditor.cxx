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
#include <dataclasses/physics/I3RecoPulse.h>

#include <boost/foreach.hpp>

class I3BadDOMAuditor : public I3Module
{
	public:
		I3BadDOMAuditor(const I3Context& context);
		void Configure();
		void Finish();
		void DetectorStatus(I3FramePtr frame);
		void DAQ(I3FramePtr frame);
	private:
		void CheckResults();
		boost::shared_ptr<const I3Vector<OMKey> > bad_doms_;
		I3GeometryConstPtr geo_;
		std::vector<std::string> pulses_;
		std::string bad_dom_list_;
		std::map<OMKey, int> pulse_counts_;
		bool bad_doms_dont_trigger_;
};

I3_MODULE(I3BadDOMAuditor);

I3BadDOMAuditor::I3BadDOMAuditor(const I3Context& context) : I3Module(context)
{
	AddParameter("BadDOMList", "List of DOMs not to check", "BadDomsList");
	AddParameter("Pulses", "Name[s] of pulse series to check",
	    "OfflinePulses");
	AddParameter("BadDOMsDontTrigger", "Fail if any DOM on the bad DOM "
	    "produces any pulses", true);
	AddOutBox("OutBox");
}

void
I3BadDOMAuditor::Configure()
{
	GetParameter("BadDOMList", bad_dom_list_);
	GetParameter("BadDOMsDontTrigger", bad_doms_dont_trigger_);

	try {
		std::string simple_name;
		GetParameter("Pulses", simple_name);
		pulses_.push_back(simple_name);
	} catch (...) {
		PyErr_Clear();
		GetParameter("Pulses", pulses_);
	}
}

void
I3BadDOMAuditor::Finish()
{
	if (!bad_doms_)
		log_fatal("Finish() called but no bad DOM list so far");

	CheckResults();
}

void
I3BadDOMAuditor::CheckResults()
{
	bool err = false;

	#define bad_dom(...) { log_error(__VA_ARGS__); err = true; continue; }

	for (I3OMGeoMap::const_iterator i = geo_->omgeo.begin();
	    i != geo_->omgeo.end(); i++) {
		if (std::find(bad_doms_->begin(), bad_doms_->end(), i->first)
		    == bad_doms_->end()) {
			// DOM is not marked bad -- make sure it triggered
			if (pulse_counts_.find(i->first) == pulse_counts_.end())
				bad_dom("OM%s not marked bad but not present "
				    "in pulse map.", i->first.str().c_str());
			if (pulse_counts_.find(i->first)->second == 0)
				bad_dom("OM%s present in pulse map but never "
				    "produced any pulses. Check calibration "
				    "constants.", i->first.str().c_str());
		} else if (bad_doms_dont_trigger_) {
			// DOM is marked bad -- make sure it did *not* trigger
			if (pulse_counts_.find(i->first) != pulse_counts_.end())
				bad_dom("OM%s marked bad but present in "
				    "pulse map.", i->first.str().c_str());
		}
	}

	#undef bad_dom

	if (err)
		log_fatal("Bad DOM list inconsistent with data. Check above.");
}
void
I3BadDOMAuditor::DetectorStatus(I3FramePtr frame)
{
	boost::shared_ptr<const I3Vector<OMKey> > new_bad_doms =
	    frame->Get<boost::shared_ptr<const I3Vector<OMKey> > >(
	    bad_dom_list_);

	if (!new_bad_doms)
		log_fatal("Bad DOMs list named %s does not exist",
		    bad_dom_list_.c_str());

	if (bad_doms_ && *new_bad_doms != *bad_doms_) {
		CheckResults();
		pulse_counts_.clear();
	}

	bad_doms_ = new_bad_doms;
	geo_ = frame->Get<I3GeometryConstPtr>();

	PushFrame(frame);
}

void
I3BadDOMAuditor::DAQ(I3FramePtr frame)
{
	if (!bad_doms_)
		log_fatal("DAQ frame but no bad DOM list so far");

	BOOST_FOREACH(const std::string &pulses_name, pulses_) {
		I3RecoPulseSeriesMapConstPtr pulses =
		    frame->Get<I3RecoPulseSeriesMapConstPtr>(pulses_name);
		if (!pulses)
			continue;

		for (I3RecoPulseSeriesMap::const_iterator i = pulses->begin();
		    i != pulses->end(); i++)
			pulse_counts_[i->first] += i->second.size();
	}

	PushFrame(frame);
}
