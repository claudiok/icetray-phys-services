/**
 * $Id: $
 * (c) 2005 IceCube Collaboration
 */

#include "icetray/I3TrayHeaders.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "phys-services/Utility.h"
#include "phys-services/I3CutsModule.h"
#include "phys-services/I3CutValues.h"

using namespace std;

I3_MODULE(I3CutsModule);

//--------------------------------------------------------------
I3CutsModule::I3CutsModule(const I3Context& ctx) : I3Module(ctx)
{
  AddOutBox("OutBox");
  
  particleName_ = "";
  AddParameter("ParticleNames", "Name of I3Particle to be used for cut calc"
	       ,particleName_);

  hitsName_ = "";
  AddParameter("HitsName", "Name of the hit series to be used for cut calc"
	       ,hitsName_);

  pulsesName_ = "";
  AddParameter("PulsesName", "Name of the pulse series to be used for cut calc"
	       ,pulsesName_);

}


//--------------------------------------------------------------
void I3CutsModule::Configure()
{
  GetParameter("ParticleNames",particleName_);   
  GetParameter("HitsName",hitsName_);
  GetParameter("PulsesName",pulsesName_);

  if (hitsName_.empty() && pulsesName_.empty()) 
    log_fatal("Either 'HitsName' or 'PulsesName' parameter HAS to be set!");
  if (!hitsName_.empty() && !pulsesName_.empty()) 
    log_fatal("Can't set both 'HitsName' and 'PulsesName' parameters!");
}


//--------------------------------------------------------------
void I3CutsModule::Physics(I3FramePtr frame)
{
  //---Get geometry......
  const I3Geometry& geometry = frame->Get<I3Geometry>();

  //---Get hit map......
  I3RecoHitSeriesMapConstPtr hitmap = 
    frame->Get<I3RecoHitSeriesMapConstPtr>(hitsName_);
  I3RecoPulseSeriesMapConstPtr pulsemap = 
    frame->Get<I3RecoPulseSeriesMapConstPtr>(pulsesName_);

  //---Get all particle names......
  set<string> particleNames = I3Functions::ParseString(particleName_);
  I3Frame::const_iterator iter;
  for(iter=frame->begin(); iter!=frame->end(); iter++) { 
    string name = iter->first;
    I3ParticleConstPtr particle = 
      dynamic_pointer_cast<const I3Particle>(iter->second);
    // this will skip all I3Vector<I3Particle>...

    if (!particle) continue;
    log_debug("Found I3Particle: '%s'",name.c_str());
    //log_trace("%s",ToString(particle).c_str());

    //---Check whether user pre-set entries......
    if ( particleName_!="" && particleNames.find(name)==particleNames.end() ) {
      log_debug("'%s' was not pre-set for processing ==> Skipping...",
		name.c_str());
      continue;
    }

    log_debug(" ---> calculating cuts for I3Particle '%s'...", name.c_str());

    I3CutValuesPtr cuts(new I3CutValues());
    if (hitmap)
      cuts->Calculate(*particle, geometry, *hitmap);
    else if (pulsemap)
      cuts->Calculate(*particle, geometry, *pulsemap);

    frame->Put(name+"Cuts", cuts);
    log_debug("%s",ToString(cuts).c_str());
  }

  PushFrame(frame,"OutBox");
}
