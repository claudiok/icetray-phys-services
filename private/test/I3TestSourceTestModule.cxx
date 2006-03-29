/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3TestSourceTestModule.cxx 2598 2005-02-04 17:18:56Z olivas $
 *
 * @file I3TestSourceTestModule.cxx
 * @version $Revision: 1.8 $
 * @date $Date: 2005-02-04 18:18:56 +0100 (Fri, 04 Feb 2005) $
 * @author olivas
 *
 */

// headers for this selection
#include <I3Test.h>
#include "phys-services/test-source/I3TestSourceTestModule.h"

// other headers
//  global header for all the IceTray stuff
#include "icetray/I3TrayHeaders.h"
#include "dataclasses/OMKey.h"
#include "dataclasses/I3Map.h"
#include "dataclasses/physics/I3AMANDAAnalogReadout.h"
#include "dataclasses/physics/I3DOMLaunch.h"
#include "dataclasses/physics/I3MCHit.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/physics/I3TWRLaunch.h"

template <class T>
I3TestSourceTestModule<T>::I3TestSourceTestModule(const I3Context& ctx) : 
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

template <class T>
I3TestSourceTestModule<T>::~I3TestSourceTestModule() {
}

// transitions
template <class T>
void I3TestSourceTestModule<T>::Configure() {
  GetParameter("NObjects", nObjects_);
  GetParameter("MapName", mapName_);
}

template <class T>
void I3TestSourceTestModule<T>::Physics(I3FramePtr frame) {

  // Get the event information out of the Frame
  const I3Map<OMKey,T>& m = frame->Get< I3Map<OMKey,T> >(mapName_);

  log_trace("m.size(): %zu",m.size());
  log_trace("nObjects_: %d",nObjects_);
 
  ENSURE(m.size() == nObjects_,"Wrong number of objects in the map.");

  PushFrame(frame,"OutBox");
}

template class I3TestSourceTestModule<I3AMANDAAnalogReadout>;
template class I3TestSourceTestModule<I3DOMLaunch>;
template class I3TestSourceTestModule<I3MCHit>;
template class I3TestSourceTestModule<I3RecoHit>;
template class I3TestSourceTestModule<I3RecoPulse>;
template class I3TestSourceTestModule<I3TWRLaunch>;

I3_MODULE(I3TestSourceTestModule<I3AMANDAAnalogReadout>);
I3_MODULE(I3TestSourceTestModule<I3DOMLaunch>);
I3_MODULE(I3TestSourceTestModule<I3MCHit>);
I3_MODULE(I3TestSourceTestModule<I3RecoHit>);
I3_MODULE(I3TestSourceTestModule<I3RecoPulse>);
I3_MODULE(I3TestSourceTestModule<I3TWRLaunch>);
