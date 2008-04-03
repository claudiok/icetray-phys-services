/**
 * $Id: $
 * (c) 2005 IceCube Collaboration
 */

#include "icetray/I3TrayHeaders.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "phys-services/Utility.h"
#include "phys-services/I3CutsModule.h"
#include "phys-services/I3TrackCutValues.h"
#include "phys-services/I3CascadeCutValues.h"

using namespace std;
using namespace I3Units;

I3_MODULE(I3CutsModule);

//--------------------------------------------------------------
I3CutsModule::I3CutsModule(const I3Context& ctx) : I3ConditionalModule(ctx)
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

  nameTag_ = "";
  AddParameter("NameTag", "Tag to add to name of output object"
	       ,nameTag_);

  timeRange_.resize(2);
  timeRange_[0] = I3Constants::dt_window_l;
  timeRange_[1] = I3Constants::dt_window_h;
  AddParameter("DirectHitsTimeRange","Time range for calculating direct hits"
	       ,timeRange_);

}


//--------------------------------------------------------------
void I3CutsModule::Configure()
{
  GetParameter("ParticleNames",particleName_);   
  GetParameter("HitsName",hitsName_);
  GetParameter("PulsesName",pulsesName_);
  GetParameter("NameTag",nameTag_);
  GetParameter("DirectHitsTimeRange",timeRange_);

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

  if (!hitmap && !pulsemap) log_fatal("The chosen reaodut is not present.");

  //if the user has specified the I3Particles to process, process them...
  if(particleName_!=""){
    //---Get all particle names......
    set<string> particleNames = I3Functions::ParseString(particleName_);
    //iterate over the set of strings to see if the frame has an object by that name...
    for (set<string>::const_iterator sit = particleNames.begin(); sit!=particleNames.end(); ++sit) {
      string name = *sit;
      if(frame->Has(name)){
	
	I3ParticleConstPtr particle = frame->Get<I3ParticleConstPtr>(name);
	if (!particle) continue;
	log_debug("Found I3Particle: '%s'",name.c_str());
	log_trace("%s",ToString(particle).c_str());
	
	log_debug(" ---> calculating cuts for I3Particle '%s'...", name.c_str());
	if(particle->IsTrack()){
	  
	  log_debug(" ---> I3Particle '%s' is a track, so proceeding accordingly...", name.c_str());
	  I3TrackCutValuesPtr cuts(new I3TrackCutValues());
	  
	  if (hitmap)
	    cuts->Calculate(*particle,geometry,*hitmap,timeRange_[0],timeRange_[1]);
	  else if (pulsemap)
	    cuts->Calculate(*particle,geometry,*pulsemap,timeRange_[0],timeRange_[1]);
	  
	  frame->Put(name+"Cuts"+nameTag_, cuts);
	  log_debug("%s",ToString(cuts).c_str());
	  
	} else if(particle->IsCascade()){
	  
	  log_debug(" ---> I3Particle '%s' is a cascade, so proceeding accordingly...", name.c_str());
	  I3CascadeCutValuesPtr cuts(new I3CascadeCutValues());
	  
	  if (hitmap)
	    cuts->Calculate(*particle,geometry,*hitmap,timeRange_[0],timeRange_[1]);
	  else if (pulsemap)
	    cuts->Calculate(*particle,geometry,*pulsemap,timeRange_[0],timeRange_[1]);
	  
	  frame->Put(name+"Cuts"+nameTag_, cuts);
	  log_debug("%s",ToString(cuts).c_str());
	  
	} else {
	  //this is probably just a failed fit; if not, something is really screwy...
	  if(particle->GetFitStatusString()=="OK"){
	    log_fatal("This I3Particle is neither a track nor a cascade!!");
	  } else {
	    log_debug("Looks like the fit for this I3Particle failed...");
	  }
	}
      }
    }
  }
  //otherwise particleName_ is empty, so process all I3Particles in the frame...
  else {

    for (I3Frame::typename_iterator iter = frame->typename_begin();
	 iter != frame->typename_end();
	 iter++) {

      string name = iter->first;
      string type = iter->second;
      
      if(type=="I3Particle"){
      
	I3ParticleConstPtr particle = dynamic_pointer_cast<const I3Particle>(frame->Get<I3FrameObjectConstPtr>(name));
	
	log_debug(" ---> calculating cuts for I3Particle '%s'...", name.c_str());
	if(particle->IsTrack()){
	  
	  log_debug(" ---> I3Particle '%s' is a track, so proceeding accordingly...", name.c_str());
	  I3TrackCutValuesPtr cuts(new I3TrackCutValues());
	  
	  if (hitmap)
	    cuts->Calculate(*particle,geometry,*hitmap,timeRange_[0],timeRange_[1]);
	  else if (pulsemap)
	    cuts->Calculate(*particle,geometry,*pulsemap,timeRange_[0],timeRange_[1]);
	  
	  frame->Put(name+"Cuts"+nameTag_, cuts);
	  log_debug("%s",ToString(cuts).c_str());
	  
	} else if(particle->IsCascade()){
	  
	  log_debug(" ---> I3Particle '%s' is a cascade, so proceeding accordingly...", name.c_str());
	  I3CascadeCutValuesPtr cuts(new I3CascadeCutValues());
	  
	  if (hitmap)
	    cuts->Calculate(*particle,geometry,*hitmap,timeRange_[0],timeRange_[1]);
	  else if (pulsemap)
	    cuts->Calculate(*particle,geometry,*pulsemap,timeRange_[0],timeRange_[1]);
	  
	  frame->Put(name+"Cuts"+nameTag_, cuts);
	  log_debug("%s",ToString(cuts).c_str());
	  
	} else {
	  //this is probably just a failed fit; if not, something is really screwy...
	  if(particle->GetFitStatusString()=="OK"){
	    log_fatal("This I3Particle is neither a track nor a cascade!!");
	  } else {
	    log_debug("Looks like the fit for this I3Particle failed...");
	  }
	}
      }
    }
  }

  PushFrame(frame,"OutBox");
}
