#include <I3Test.h>
#include "icetray/I3Tray.h"
#include "icetray/modules/TrashCan.h"
#include "phys-services/test-source/I3TestSourceTestModule.h"
#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"
#include "phys-services/source/I3Muxer.h"

#include "boost/random.hpp"

#include "phys-services/test-source/I3TestSource.h"
#include "dataclasses/I3Vector.h"
#include "dataclasses/physics/I3MCHit.h"

const unsigned NOBJECTS = 10;

template <> void I3TestSource<I3Vector<I3MCHit> >::Randomize(I3Vector<I3MCHit>& p){};
template class I3TestSource<I3Vector<I3MCHit> >;
I3_MODULE(I3TestSource<I3Vector<I3MCHit> >);

template <>
void I3TestSourceTestModule<I3Vector<I3MCHit> >::Physics(I3FramePtr frame) {
  // Get the event information out of the Frame
  const I3Map<OMKey,I3Vector<I3MCHit> >& m = 
    frame->Get< I3Map<OMKey,I3Vector<I3MCHit> > >(mapName_);

  log_trace("m.size(): %zu",m.size());
 
  ENSURE(m.size() == NOBJECTS,"Wrong number of objects in the map.");

  PushFrame(frame,"OutBox");
}

template class I3TestSourceTestModule<I3Vector<I3MCHit> >;
I3_MODULE(I3TestSourceTestModule<I3Vector<I3MCHit> >);


TEST_GROUP(I3TestSource);

TEST(multiple_MCHits){

  I3Tray tray;


  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",2);
  tray.AddModule("I3Muxer","muxer");
  tray.AddModule("I3TestSource<I3Vector<I3MCHit> >","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",NOBJECTS);
  tray.AddModule("I3TestSourceTestModule<I3Vector<I3MCHit> >","test_module")
    ("MapName","ParticleMap");
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}

