#include "phys-services/source/I3MCCalibrationService.h"
#include "dataclasses/calibration/I3Calibration.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "dataclasses/I3Units.h"
#include "icetray/I3TrayHeaders.h"

I3CalibrationConstPtr
I3MCCalibrationService::GetCalibration(I3Time time)
{
  return static_cast<I3CalibrationConstPtr>(calibration_);
}  

void I3MCCalibrationService::Fill(I3GeometryConstPtr geo){

  log_debug("Fill...");
    const I3OMGeoMap& om_geo = geo->omgeo;

    I3OMGeoMap::const_iterator iter;

    calibration_ = I3CalibrationPtr(new I3Calibration);

    I3Time start(2000,0);
    I3Time end(3000,0);

    calibration_->startTime = start;
    calibration_->endTime = end;
     //changed all inice to om_geo
    for( iter  = om_geo.begin(); iter != om_geo.end(); iter++ ){
	OMKey thiskey = iter->first;

	I3DOMCalibration domCalib;

	//fadcGain_ = 2.5*9;

	domCalib.SetATWDGain(0, -16.0);
	domCalib.SetATWDGain(1, -2.0);
	domCalib.SetATWDGain(2, -0.25);
	
	QuadraticFit qfit0,qfit1;
	
	qfit0.quadFitA = 2.5858788;
	qfit0.quadFitB = 0.013337472;
	qfit0.quadFitC = NAN;
	
	qfit1.quadFitA = 2.3853257;
	qfit1.quadFitB = 0.014224272;
	qfit1.quadFitC = NAN; 

	domCalib.SetATWDFreqFit(0,qfit0);
	domCalib.SetATWDFreqFit(1,qfit1);

	LinearFit hvgainfit;	
	hvgainfit.intercept = -15.1997;
	hvgainfit.slope = 7.0842533;

    	domCalib.SetHVGainFit(hvgainfit);

	for( unsigned int channel = 0; channel < 3; ++channel )
	{
	    for( unsigned int id = 0; id <= 1; ++id )
	    {
		for( unsigned int bin = 0; bin < 128; ++bin )
		{
		    LinearFit binfit;
		    binfit.slope = -0.002*I3Units::V;
		    binfit.intercept = 2.9*I3Units::V;
	   
		    domCalib.SetATWDBinCalibFit(id,channel,bin,
						   binfit);
		}
	    }
	}
	calibration_->domCal[thiskey] = domCalib;
    }
}


