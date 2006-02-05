/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3CalibrateStatusModule.cxx 7445 2005-05-09 15:33:59Z aya $
 *
 * @file I3CalibrateStatusModule.cxx 
 * @brief Implementation of the I3CalibrateStatusModule classs
 * @version $Revision: 1.2 $
 * @date $Date: 2005-05-09 11:33:59 -0400 (Mon, 09 May 2005) $
 * @author pretz
 */


#include "phys-services/source/I3CalibrateStatusModule.h"

#include "dataclasses/I3DigitalReadout.h"
#include "dataclasses/I3DOMLaunch.h"
#include "dataclasses/I3Event.h"
#include "dataclasses/I3InIceCalibration.h"
#include "dataclasses/I3Calibration.h"
#include "dataclasses/I3DetectorStatus.h"
#include "dataclasses/I3Units.h"

I3_MODULE(I3CalibrateStatusModule);

I3CalibrateStatusModule::I3CalibrateStatusModule(const I3Context& context) : 
  I3PhysicsModule(context)
{
  AddOutBox("OutBox");
}

void I3CalibrateStatusModule::DetectorStatus(I3Frame& frame)
{
  I3DetectorStatus& status = GetDetectorStatus(frame);
  I3Calibration& calibration = GetCalibration(frame);
  I3InIceCalibration& inicecalib = calibration.GetInIceCalibration();

  I3IceCubeDOMStatusDict& icecubestatus = status.GetIceCubeDOMStatus();
  
  I3IceCubeDOMStatusDict::iterator iter;
  for(iter = icecubestatus.begin() ; iter != icecubestatus.end() ; iter++)
    {
      OMKey thekey = iter->first;
      I3DOMStatusPtr dstatptr = iter->second;
      I3RawDOMStatusPtr rawstatus = dstatptr->GetRawStatus(); 
      I3CalibratedDOMStatusPtr 
	calibratedstatus(new I3CalibratedDOMStatus());      
      dstatptr->SetCalibratedStatus(calibratedstatus);
      assert(inicecalib.count(thekey)>0);
      I3DOMCalibrationPtr domcalib = inicecalib[thekey];
      DoTheCalibration(rawstatus,calibratedstatus,domcalib);
    }

  PushFrame(frame,"OutBox");
}

void I3CalibrateStatusModule::
DoTheCalibration(I3RawDOMStatusPtr rawstatus,
		 I3CalibratedDOMStatusPtr calibratedstatus,
		 I3DOMCalibrationPtr calib)
{
    /**
     * Calculate the SPE mean and PMT gain
     * Use the supplied HVGain relation: 
     * log(10)Gain = slope*log(10)V + intercept
     */
    double predictedSpeMean;
    double log_gain = 0.0;
    double gain = 0.0;
    double currentVoltage=(rawstatus->GetPMTHV()/I3Units::volt);
    const LinearFit hvgain = calib->GetHVGainFit();
  
    if( currentVoltage > 0.0 )
    {
	log_gain = hvgain.slope*log10(currentVoltage) + hvgain.intercept;
	gain = pow(10.0,log_gain);
	predictedSpeMean = gain*I3Units::eSI*1.0e12;
	
	log_trace("LOOK: predictedSPEMean %f", predictedSpeMean);
    }
  
    else
    {
	log_warn("DOM voltage is zero. No SPEMean or PMTGain possible");
	predictedSpeMean = 0.0;
    }

    //Michelangelo's hack for MC data that doesn't have the charge histograms
    if( hvgain.intercept == 0.0 && hvgain.slope == 0.0 )
    {
	predictedSpeMean = 1.6*I3Units::pC; //this is just some average, reasonable value
    }
  
    calibratedstatus->SetPMTGain(gain);
    calibratedstatus->SetSPEMean(predictedSpeMean*I3Units::pC); 

    /**
     * Calculate the sampling rate
     * Use the sampling rate relation:
     * sampling rate (MHz) = 20.0*(slope*DAC[0,4]+intercept)
     */
    double rateCorrected=0; //sampling rate in MHz

    for (int chip=0; chip<2; chip++)
    {
	QuadraticFit atwdQFit  = calib->GetATWDFreqFit(chip);

	if( isnan(atwdQFit.quadFitC) ) // Old style linear fit
	{
	    double slope = atwdQFit.quadFitB;
	    double intercept = atwdQFit.quadFitA;
	    double dacTriggerBias =  rawstatus->GetDACTriggerBias(chip);
	  
	    rateCorrected = (slope * dacTriggerBias + intercept)*20.;  //
	    log_trace("filled rate corrected %f MHz, for chip %d", rateCorrected, chip);
	  
	    if(chip==0)
		calibratedstatus->SetSamplingRateA(rateCorrected / I3Units::microsecond);
	    
	    else if(chip==1)
		calibratedstatus->SetSamplingRateB(rateCorrected / I3Units::microsecond);
	    
	    else 
		log_error("atwd chip %d not available", chip);
	}

	else
	{
	  if(atwdQFit.quadFitC == 0.0)
	    {
	      log_warn("Found a quadratic fit with C=0.0, are you sure this is is a quadratic fit??");
	    }
	  log_error("Quadratic fit found.  I need to be implemented!!");
	  // @todo implement this
	}
    }
}
