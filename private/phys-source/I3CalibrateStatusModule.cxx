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


#include "phys-source/I3CalibrateStatusModule.h"

#include "dataclasses/I3DigitalReadout.h"
#include "dataclasses/I3DOMLaunch.h"
#include "dataclasses/I3Event.h"
#include "dataclasses/I3InIceCalibration.h"
#include "dataclasses/I3Calibration.h"
#include "dataclasses/I3DetectorStatus.h"

I3CalibrateStatusModule::I3CalibrateStatusModule(I3Context& context) : 
  I3PhysicsModule(context)
{
  AddOutBox("OutBox");
}

void I3CalibrateStatusModule::DetectorStatus(I3Frame& frame)
{
  I3DetectorStatus& status = GetDetectorStatus(frame);
  I3Calibration& calibration = GetCalibration(frame);
  I3InIceCalibration& inicecalib = calibration.GetInIceCalibration();

  I3IceCubeStatus& icecubestatus = status.GetIceCubeStatus();
  
  I3IceCubeStatus::iterator iter;
  for(iter = icecubestatus.begin() ; iter != icecubestatus.end() ; iter++)
    {
      OMKey thekey = iter->first;
      I3RawDOMStatusPtr rawstatus = iter->second.GetRawStatus();
      I3CalibratedDOMStatusPtr 
	calibratedstatus(new I3CalibratedDOMStatus());      
      iter->second.SetCalibratedStatus(calibratedstatus);
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
  //currently this method just calibrates the position of the SPE peak

  // the proceedure here is to find first the charge histogram 
  // that is closest to our hv, then the one that is next closest.
  // Do it this way 'cause sometimes we're interpolating and 
  // sometimes extrapolating.

  int closestVoltage = 0;
  int currentVoltage=(unsigned int)rawstatus->GetPMTHV();
  map<unsigned int,ChargeHistogram>::iterator iter;
  for(iter = calib->GetChargeHistograms().begin() ; 
      iter!= calib->GetChargeHistograms().end() ; 
      iter++)
    {
      if(iter->second.convergent)
	{
	  unsigned int currentDist = abs(closestVoltage - currentVoltage);
	  unsigned int thisDist = abs(((int)iter->first) - currentVoltage);
	  if(thisDist < currentDist)
	    closestVoltage = iter->first;
	}
    }
  
  int nextClosestVoltage = 0;
  for(iter = calib->GetChargeHistograms().begin() ; 
      iter!= calib->GetChargeHistograms().end() ; 
      iter++)
    {
      if(iter->second.convergent)
	{
	  unsigned int currentDist = abs(nextClosestVoltage - currentVoltage);
	  unsigned int thisDist = abs(((int)iter->first) - currentVoltage);
	  if(thisDist < currentDist && closestVoltage != (int)iter->first)
	    nextClosestVoltage = iter->first;
	}
    }

  // just use a linear extrapolation of form y = m * x + b
  // Fancier later if we want
  double y1 = calib->GetChargeHistograms()[closestVoltage].gaussianMean;
  double y2 = calib->GetChargeHistograms()[nextClosestVoltage].gaussianMean;
  double x1 = closestVoltage;
  double x2 = nextClosestVoltage;
  double m = (y1 - y2) / (x1 - x2);
  double b = y1 - m * x1;
  
  double predictedSpeMean = m * rawstatus->GetPMTHV() + b;
  
  log_trace("LOOK: predictedSPEMean %f",predictedSpeMean);
//   cout<<"LOOK: found closest: "<<closestVoltage<<endl;
//   cout<<"LOOK: found next-closest: "<<nextClosestVoltage<<endl;
//   cout<<"LOOK: real: "<<rawstatus->GetPMTHV()<<endl;

  calibratedstatus->SetSPEMean(predictedSpeMean);
 //a
  double rateCorrected=0; //sampling rate in MHz

  for (int chip=0; chip<2; chip++)
    {
      double slope = calib->GetATWDfreqSlope(chip);
      double intercept = calib->GetATWDfreqIntercept(chip);
      double dacTriggerBias =  rawstatus->GetDACTriggerBias(chip);

      rateCorrected = (slope * dacTriggerBias + intercept)*20.;  //
      log_trace("filled rate corrected %f MHz, for chip %d", rateCorrected, chip);

      if(chip==0)calibratedstatus->SetSamplingRateA(rateCorrected / I3Units::microsecond);
      else if(chip==1)calibratedstatus->SetSamplingRateB(rateCorrected / I3Units::microsecond);
      else log_error("atwd chip %d not available", chip);
    }
  //a
}
