#include <I3Test.h>

#include "phys-services/source/I3CalibrateStatusModule.h"
#include "dataclasses/status/I3MCRawDOMStatus.h"
#include "dataclasses/I3Units.h"

#include <sstream>
#include <iostream>

using namespace std;

// Test some of Calibrate Module functionality
TEST_GROUP(CalibrateStatusModuleStatus);

TEST(DoCalibTest1)
    {
    I3MCRawDOMStatusPtr rawstatus(new I3MCRawDOMStatus());
    I3CalibratedDOMStatusPtr calibratedstatus(new I3CalibratedDOMStatus());
    I3DOMCalibrationPtr calib(new I3DOMCalibration());
    
    //Set some values
    rawstatus->SetPMTHV(1400*I3Units::V);
    rawstatus->SetDACTriggerBias(850,0);
    rawstatus->SetDACTriggerBias(850,1);
    QuadraticFit qfit0,qfit1;
    //Values from an actual DOMCAL file.
    qfit0.quadFitA = 2.5858788;
    qfit0.quadFitB = 0.013337472;
    qfit0.quadFitC = NAN;  //Linear fit here
    qfit1.quadFitA = 2.3853257;
    qfit1.quadFitB = 0.014224272;
    qfit1.quadFitC = NAN;  //Linear fit here

    calib->SetATWDFreqFit(0,qfit0);
    calib->SetATWDFreqFit(1,qfit1);

    LinearFit hvgainfit;
    hvgainfit.intercept = -15.1997;
    hvgainfit.slope = 7.0842533;
    
    calib->SetHVGainFit(hvgainfit);

    I3CalibrateStatusModule::DoTheCalibration(rawstatus,
					      calibratedstatus,
					      *calib);

    //Compare the return values to values calculated by hand.

    ENSURE_DISTANCE(1.9632,calibratedstatus->GetSPEMean()/I3Units::pC*1.0E12,
		    0.001,"Failed to return the proper SPEMean value");
    ENSURE_DISTANCE(278.455,
		    calibratedstatus->GetSamplingRateA()*I3Units::microsecond,
                    0.001,"Failed to return proper ATWD-A sampling rate");
    ENSURE_DISTANCE(289.519,
 		    calibratedstatus->GetSamplingRateB()*I3Units::microsecond,
                    0.001,"Failed to return proper ATWD-B sampling rate");


}

