#include <I3Test.h>
#include "icetray/I3Tray.h"
#include "icetray/modules/TrashCan.h"
#include "phys-services/test-source/I3TestSourceTestModule.h"
#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"
#include "phys-services/source/I3Muxer.h"


TEST_GROUP(I3TestSource);

TEST(ten_I3Particles){

  I3Tray tray;

  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",10);
  tray.AddModule("I3Muxer","muxer");
  tray.AddModule("I3TestSource<I3Particle>","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",10);
  tray.AddModule("I3TestSourceTestModule","test_module")
    ("MapName","ParticleMap")
    ("NObjects",10);
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}
