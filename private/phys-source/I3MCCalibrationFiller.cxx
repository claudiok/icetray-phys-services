#include "phys-source/I3MCCalibrationFiller.h"
#include "dataclasses/I3Calibration.h"
#include "dataclasses/I3DOMCalibration.h"
#include "dataclasses/I3InIceGeometry.h"
#include "dataclasses/I3Geometry.h"

double I3MCCalibrationFiller::CONVERSION_FACTOR = -0.0021;

I3MCCalibrationFiller::I3MCCalibrationFiller(I3Context& context) 
: I3PhysicsModule(context)
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

void I3MCCalibrationFiller::Calibration(I3Frame& frame)
{
    log_debug("I3MCCalibrationFiller::Calibration");

    I3Geometry& geo = GetGeometry(frame);
    I3InIceGeometry& inice = geo.GetInIceGeometry();

    I3InIceGeometry::iterator iter;

    I3Calibration& calib = GetCalibration(frame);

    for( iter  = inice.begin(); 
	 iter != inice.end(); 
	 iter++ )
    {
	OMKey thiskey = iter->first;

	I3DOMCalibrationPtr domCalib(new I3DOMCalibration());
	
	domCalib->SetATWDGain(0, atwd0gain_, 0.0);
	domCalib->SetATWDGain(1, atwd1gain_, 0.0);
	domCalib->SetATWDGain(2, atwd2gain_, 0.0);

	double pedestal = 0.0;
	double gain = fadcGain_;
	domCalib->SetFADCParameters(pedestal, gain);
       
	for( int channel = 0; channel < 3; ++channel )
	{
	    for( int id = 0; id < 1; ++id )
	    {
		for( int bin = 0; bin < 128; ++bin )
		{
		    double slope = CONVERSION_FACTOR;
	   
		    domCalib->SetATWDParameters(id,channel,bin,
						slope,0.0,0.0);
		}
	    }
	}
	
	calib.GetInIceCalibration()[thiskey] = domCalib;
    }
    
    PushFrame(frame,"OutBox");
}


