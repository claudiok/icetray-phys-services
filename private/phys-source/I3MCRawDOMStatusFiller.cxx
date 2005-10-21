#include "phys-source/I3MCRawDOMStatusFiller.h"
#include "dataclasses/I3RawDOMStatus.h"
#include "dataclasses/I3MCRawDOMStatus.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3DetectorStatus.h"

I3_MODULE(I3MCRawDOMStatusFiller);

I3MCRawDOMStatusFiller::I3MCRawDOMStatusFiller(const I3Context& context) : 
  I3PhysicsModule(context)
{
    triggerMode_ = 2;
    AddParameter("triggerMode", "trigger mode",
		 triggerMode_);
    
    lcMode_ = 4;
    AddParameter("lcMode", "local coincidence mode",
		 lcMode_);
    
    pmtHV_ = 1350*I3Units::volt;
    AddParameter("pmtHV", "pmt high voltage", 
		 pmtHV_);
    
    speThreshold_ = 4.0*I3Units::mV;
    AddParameter("speThreshold", "discriminator threshold", 
		 speThreshold_);

    lcWindowUpPre_ = -800.0*I3Units::ns;
    AddParameter("lcWindowUpPre", "local coincidence window UpPre", 
		 lcWindowUpPre_);
    
    lcWindowDownPre_ = -800.0*I3Units::ns;
    AddParameter("lcWindowDownPre", "local coincidence window DownPre", 
		 lcWindowDownPre_);

    lcWindowUpPost_ = 800.0*I3Units::ns;
    AddParameter("lcWindowUpPost", "local coincidence window UpPost", 
		 lcWindowUpPost_);

    lcWindowDownPost_ = 800.0*I3Units::ns;
    AddParameter("lcWindowDownPost", "local coincidence window DownPost", 
		 lcWindowDownPost_);

    atwdAOn_ = true;
    AddParameter("atwdAOn", "Is ATWD A on?", atwdAOn_);
    
    atwdBOn_ = true;
    AddParameter("atwdBOn", "Is ATWD B on?", atwdBOn_);
    
    fadcOn_ = true;
    AddParameter("fadcOn", "Is FADC on?", fadcOn_);

    atwd0Nbins_ = 128;
    AddParameter("atwd0Nbins", 
		 "number of samples in ATWD channel 0",
		 atwd0Nbins_);
    
    atwd1Nbins_ = 128;
    AddParameter("atwd1Nbins", 
		 "number of samples in ATWD channel 1",
		 atwd1Nbins_);

    atwd2Nbins_ = 128;
    AddParameter("atwd2Nbins", 
		 "number of samples in ATWD channel 2",
		 atwd2Nbins_);

    atwd3Nbins_ = 128;
    AddParameter("atwd3Nbins", 
		 "number of samples in ATWD channel 3",
		 atwd3Nbins_);

    fadcNbins_ = 256;
    AddParameter("fadcNbins", 
		 "number of samples in FADC",
		 fadcNbins_);

    AddOutBox("OutBox");
}

void I3MCRawDOMStatusFiller::Configure()
{
    GetParameter("triggerMode", triggerMode_);
 
    if ( triggerMode_ != 2 )
    {
	log_warn("Unsupported trigger mode! Setting to 2:SPE");
	triggerMode_ = 2;
    }
    
    GetParameter("lcMode", lcMode_);

    if ( lcMode_ != 4 )
    {
	log_warn("Unsupported LC mode! Setting to 4:UpAndDown");
	lcMode_ = 4;
    }
    
    /*
    if ( lcMode_ < 0 || lcMode_ > 4 )
    {
	log_fatal("Bad LC mode! Use modes 0:LCOff, 1:UpOrDown, 2:Up, 3:Down, 4:UpAndDown");
    }
    */

    GetParameter("lcWindowUpPre", lcWindowUpPre_);
    GetParameter("lcWindowDownPre", lcWindowDownPre_);
    GetParameter("lcWindowUpPost", lcWindowUpPost_);
    GetParameter("lcWindowDownPost", lcWindowDownPost_);
    
    GetParameter("pmtHV", pmtHV_);
    GetParameter("speThreshold", speThreshold_);
    
    GetParameter("atwdAOn", atwdAOn_);
    GetParameter("atwdBOn", atwdBOn_);
    GetParameter("fadcOn", fadcOn_);

    GetParameter("atwd0Nbins", atwd0Nbins_);
    GetParameter("atwd1Nbins", atwd1Nbins_);
    GetParameter("atwd2Nbins", atwd2Nbins_);
    GetParameter("atwd3Nbins", atwd3Nbins_);

    GetParameter("fadcNbins", fadcNbins_);
}


void I3MCRawDOMStatusFiller::DetectorStatus(I3Frame& frame)
{
    log_debug("I3MCRawDOMStatusFiller::DetectorStatus");

    I3Geometry& geo = GetGeometry(frame);
    I3InIceGeometry& inice = geo.GetInIceGeometry();

    I3InIceGeometry::iterator iter;

    I3DetectorStatus& status = GetDetectorStatus(frame);

    // Trigger mode
    I3RawDOMStatus::TrigMode triggerMode = I3RawDOMStatus::SPE;

    // What's the LC mode?
    I3RawDOMStatus::LCMode lcMode;

    if ( lcMode_ == 0 )
    {
	lcMode = I3RawDOMStatus::LCOff;
    }
    
    else if ( lcMode_ == 1 )
    {
	lcMode = I3RawDOMStatus::UpOrDown;
    }
    
    else if ( lcMode_ == 2 )
    {
	lcMode = I3RawDOMStatus::Up;
    }
    
    else if ( lcMode_ == 3 )
    {
	lcMode = I3RawDOMStatus::Down;
    }
    
    else if ( lcMode_ == 4 )
    {
	lcMode = I3RawDOMStatus::UpAndDown;
    }
    
    // Is ATWD A on?
    I3RawDOMStatus::OnOff atwdAOn;

    if ( atwdAOn_ )
    {
	atwdAOn = I3RawDOMStatus::On;
    }
    
    else 
    {
	atwdAOn = I3RawDOMStatus::Off;
    }
    
    // Is ATWD B on?
    I3RawDOMStatus::OnOff atwdBOn;

    if ( atwdBOn_ )
    {
	atwdBOn = I3RawDOMStatus::On;
    }
    
    else 
    {
	atwdBOn = I3RawDOMStatus::Off;
    }

    // Is the FADC on?
    I3RawDOMStatus::OnOff fadcOn;

    if ( fadcOn_ )
    {
	fadcOn = I3RawDOMStatus::On;
    }
    
    else 
    {
	fadcOn = I3RawDOMStatus::Off;
    }

    for( iter  = inice.begin(); 
	 iter != inice.end(); 
	 iter++ )
    {
	OMKey thiskey = iter->first;

	I3MCRawDOMStatusPtr raw(new I3MCRawDOMStatus());

	raw->SetTrigMode(triggerMode);
	raw->SetLCMode(lcMode);
	
	raw->SetLCWindowUpPre(lcWindowUpPre_);
	raw->SetLCWindowDownPre(lcWindowDownPre_);
	raw->SetLCWindowUpPost(lcWindowUpPost_);
	raw->SetLCWindowDownPost(lcWindowDownPost_);

	raw->SetStatusATWD_A(atwdAOn);
	raw->SetStatusATWD_B(atwdBOn);
	raw->SetStatusFADC(fadcOn);
	
	raw->SetPMTHV(pmtHV_);
	raw->SetSingleSPEThreshold(speThreshold_);
	raw->SetFEPedestal(2.6*I3Units::volt);
    
	raw->SetNBinsATWD(0, atwd0Nbins_);
	raw->SetNBinsATWD(1, atwd1Nbins_);
	raw->SetNBinsATWD(2, atwd2Nbins_);

	raw->SetNBinsFADC(fadcNbins_);

	status.GetIceCubeStatus()[thiskey].SetRawStatus(raw);
    }
    
    PushFrame(frame,"OutBox");
}


