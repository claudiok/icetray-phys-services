#include "phys-source/I3TestSources.h"

#include "dataclasses/I3Event.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3OMSelectionDict.h"
#include "dataclasses/I3DigitalReadout.h"
#include "dataclasses/I3DigitalLaunch.h"
#include "dataclasses/I3DOMLaunch.h"
#include "dataclasses/I3MCCascade.h"

ClassImp(I3TestSources);

I3TestSources::I3TestSources(I3Context& ctx) : 
    I3PhysicsModule(ctx)
{
    AddOutBox("OutBox");
}

I3TestSources::~I3TestSources()
{}

void I3TestSources::Configure()
{
    log_info("I3TestSources::Configure");
}

void I3TestSources::DumpMCCascade(I3MCEvent* event)
{
    I3ParticleMultiMap& pmm_inice = 
	event->GetMCParticleData().GetInIceParticles();
    
    I3ParticleMultiMap::iterator pmm_iter;
    
    double energy;
    
    I3Position position;
    I3Direction direction;
    
    double x, y, z;
    double px, py, pz;

    for ( pmm_iter  = pmm_inice.begin();
	  pmm_iter != pmm_inice.end();
	  pmm_iter++ )
    {

	I3MCCascadePtr cascade = 
	    dynamic_pointer_cast<I3MCCascade>(pmm_iter->second);

	energy = cascade->GetEnergy()/I3Units::GeV;
	position = cascade->GetPos();
	direction = cascade->GetDir();

	fCascadePositionTrue = position;
	
	x = position.GetX()/I3Units::m;
	y = position.GetY()/I3Units::m;
	z = position.GetZ()/I3Units::m;
	
	px = direction.GetX();
	py = direction.GetY();
	pz = direction.GetZ();
	
	cout<<"MCCascade info:"<<endl;
	cout<<"---------------"<<endl;
	cout<<"Energy = "<< energy <<" GeV"<<endl;
	cout<<"Position = "
	    << x <<" "
	    << y <<" "
	    << z <<" m"<<endl;
	cout<<"Direction = "
	    << px <<" "
	    << py <<" "
	    << pz <<endl;
    }
}

void I3TestSources::DumpGeometry(I3Geometry& geometry)
{
    I3InIceGeometry& inIceGeo = geometry.GetInIceGeometry();

    I3InIceGeometry::iterator geo_iter;
    
    for ( geo_iter  = inIceGeo.begin();
	  geo_iter != inIceGeo.end();
	  geo_iter++ )
    {
	I3OMGeo::EOMType type = geo_iter->second->GetOMType();
	
	if ( type == I3OMGeo::IceCube ) 
	{
	    cout<< geo_iter->first <<" "
		<< geo_iter->second->GetPos().GetX() <<" "
		<< geo_iter->second->GetPos().GetY() <<" "
		<< geo_iter->second->GetPos().GetZ() <<endl;
	}	
    }
    
}

void I3TestSources::Calibration(I3Frame& frame)
{
    log_info("I3TestSources::Calibration");
}

void I3TestSources::DetectorStatus(I3Frame& frame)
{
    log_info("I3TestSources::DetectorStatus");
}

void I3TestSources::Physics(I3Frame& frame)
{
    log_info("I3TestSources::Physics");

    I3Event& event = GetEvent(frame);

    if ( ! HasMCEvent(frame) )
    {
	log_info("No MCEvent");
    }

    //I3MCEvent& mcevent = GetMCEvent(frame);
    //mceevnt.ToStream(cout);

    //I3MCEventPtr mcevent = frame.Get<I3MCEventPtr>("Physics");
    //mcevent->ToStream(cout);

    I3MCEvent* mcevent = dynamic_cast<I3MCEvent*>(&event);
    //mcevent->ToStream(cout);
    
    DumpMCCascade(mcevent);

    // Get the geometry from the frame
    I3Geometry& geometry = GetGeometry(frame);
    //DumpGeometry(geometry);
    
    // Get the InIce geometry
    I3InIceGeometry& inIceGeo = geometry.GetInIceGeometry();

    PushFrame(frame,"OutBox");
}
