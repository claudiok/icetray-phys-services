#include "phys-services/source/I3MCCalibrationFiller.h"
#include "dataclasses/calibration/I3Calibration.h"
#include "dataclasses/calibration/I3DOMCalibration.h"
#include "dataclasses/geometry/I3InIceGeometry.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "icetray/I3Frame.h"
#include "dataclasses/I3Units.h"

I3_MODULE(I3MCCalibrationFiller);

I3MCCalibrationFiller::I3MCCalibrationFiller(const I3Context& context) 
: I3Module(context)
{
    atwd0gain_ = -16.0;
    AddParameter("ATWD0gain", "ATWD0 gain", atwd0gain_);
    
    atwd1gain_ = -2.0;
    AddParameter("ATWD1gain", "ATWD1 gain", atwd1gain_);
    
    atwd2gain_ = -0.25;
    AddParameter("ATWD2gain", "ATWD2 gain", atwd2gain_);
    
    fadcGain_ = 2.5*9;
    AddParameter("FADCgain", "FADC gain", fadcGain_);
    
    AddOutBox("OutBox");  
} 
 
void I3MCCalibrationFiller::Configure()
{
    GetParameter("ATWD0gain", atwd0gain_);
    GetParameter("ATWD1gain", atwd1gain_);
    GetParameter("ATWD2gain", atwd2gain_);

    GetParameter("FADCgain", fadcGain_);
}

void I3MCCalibrationFiller::Calibration(I3FramePtr frame)
{
    log_debug("I3MCCalibrationFiller::Calibration");

    const I3Geometry& geo = frame->Get<I3Geometry>("Geometry");
    const I3InIceGeometry& inice = geo.GetInIceGeometry();

    I3InIceGeometry::const_iterator iter;

    const I3Calibration& calib = frame->Get<I3Calibration>("Calibration");

    for( iter  = inice.begin(); 
	 iter != inice.end(); 
	 iter++ )
    {
	OMKey thiskey = iter->first;

	I3DOMCalibrationPtr domCalib(new I3DOMCalibration());
	
	domCalib->SetATWDGain(0, atwd0gain_);
	domCalib->SetATWDGain(1, atwd1gain_);
	domCalib->SetATWDGain(2, atwd2gain_);

	for( unsigned int channel = 0; channel < 3; ++channel )
	{
	    for( unsigned int id = 0; id <= 1; ++id )
	    {
		for( unsigned int bin = 0; bin < 128; ++bin )
		{
		    LinearFit binfit;
		    binfit.slope = -0.002*I3Units::V;
		    binfit.intercept = 2.9*I3Units::V;
	   
		    domCalib->SetATWDBinCalibFit(id,channel,bin,
						   binfit);
		}
	    }
	}
	
	const_cast<I3InIceCalibration&>(calib.GetInIceCalibration())[thiskey] = domCalib;
    }
    
    PushFrame(frame,"OutBox");
}


