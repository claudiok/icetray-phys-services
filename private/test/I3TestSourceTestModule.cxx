/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3GeometrySelector.cxx 2598 2005-02-04 17:18:56Z olivas $
 *
 * @file I3GeometrySelector.cxx
 * @version $Revision: 1.8 $
 * @date $Date: 2005-02-04 18:18:56 +0100 (Fri, 04 Feb 2005) $
 * @author olivas
 *
 * This class shows how to add a Selection to the event.
*/

// headers for this selection
#include <I3Test.h>
#include "phys-services/test-source/I3TestSourceTestModule.h"

// other headers
//  global header for all the IceTray stuff
#include "icetray/I3TrayHeaders.h"
#include "dataclasses/OMKey.h"
#include "dataclasses/I3Map.h"
#include "dataclasses/physics/I3Particle.h"


I3_MODULE(I3TestSourceTestModule);

I3TestSourceTestModule::I3TestSourceTestModule(const I3Context& ctx) : 
  I3Module(ctx),
  nObjects_(1),
  mapName_("Default")
{
  AddOutBox("OutBox");
  
  AddParameter("NObjects", 
	       "Number of objects in the frame", 
	       nObjects_);
  AddParameter("MapName", 
	       "Name of the map that contains the objects", 
	       mapName_);
}

I3TestSourceTestModule::~I3TestSourceTestModule() {
}

// transitions
void I3TestSourceTestModule::Configure() {
  GetParameter("NObjects", nObjects_);
  GetParameter("MapName", mapName_);
}

void I3TestSourceTestModule::Physics(I3FramePtr frame) {

  // Get the event information out of the Frame
  const I3Map<OMKey,I3Particle>& particleMap = frame->Get< I3Map<OMKey,I3Particle> >(mapName_);

  log_trace("particleMap.size(): %zu",particleMap.size());
  log_trace("nObjects_: %d",nObjects_);
 
  ENSURE(particleMap.size() == nObjects_,"Wrong number of objects in the map.");

  PushFrame(frame,"OutBox");
}


