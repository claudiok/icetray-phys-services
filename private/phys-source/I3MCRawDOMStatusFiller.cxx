#include "phys-source/I3MCRawDOMStatusFiller.h"
#include "dataclasses/I3RawDOMStatus.h"
#include "dataclasses/I3MCRawDOMStatus.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3DetectorStatus.h"

I3MCRawDOMStatusFiller::I3MCRawDOMStatusFiller(I3Context& context) : 
  I3PhysicsModule(context)
{
    pmtHV_ = 1200*I3Units::volt;
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

    AddOutBox("OutBox");
}

void I3MCRawDOMStatusFiller::DetectorStatus(I3Frame& frame)
{
    log_debug("I3MCRawDOMStatusFiller::DetectorStatus");

    I3Geometry& geo = GetGeometry(frame);
    I3InIceGeometry& inice = geo.GetInIceGeometry();

    I3InIceGeometry::iterator iter;

    I3DetectorStatus& status = GetDetectorStatus(frame);

    for( iter  = inice.begin(); 
	 iter != inice.end(); 
	 iter++ )
    {
	OMKey thiskey = iter->first;

	I3MCRawDOMStatusPtr raw(new I3MCRawDOMStatus());

	//I3RawDOMStatus::TrigMode trigMode = I3RawDOMStatus::SPE;

	raw->SetTrigMode(I3RawDOMStatus::SPE);
	raw->SetLCMode(I3RawDOMStatus::UpAndDown);
	
	raw->SetLCWindowUpPre(lcWindowUpPre_);
	raw->SetLCWindowDownPre(lcWindowDownPre_);
	raw->SetLCWindowUpPost(lcWindowUpPost_);
	raw->SetLCWindowDownPost(lcWindowDownPost_);

	raw->SetStatusATWD_A(I3RawDOMStatus::On);
	raw->SetStatusATWD_B(I3RawDOMStatus::On);
	raw->SetStatusFADC(I3RawDOMStatus::On);
	
	raw->SetPMTHV(pmtHV_);
	raw->SetSingleSPEThreshold(speThreshold_);
	raw->SetFEPedestal(0.0*I3Units::mV);
    
	status.GetIceCubeStatus()[thiskey].SetRawStatus(raw);
    }
    
    PushFrame(frame,"OutBox");
}


