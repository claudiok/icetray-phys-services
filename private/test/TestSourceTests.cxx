#include <I3Test.h>
#include "icetray/I3Tray.h"
#include "icetray/modules/TrashCan.h"
#include "phys-services/test-source/I3TestSourceTestModule.h"
#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"
#include "phys-services/source/I3Muxer.h"

#include "boost/random.hpp"

TEST_GROUP(I3TestSource);

TEST(multiple_DOMLaunches){

  I3Tray tray;

  boost::rand48 rng(static_cast<int>(time(0)));
  boost::uniform_smallint<unsigned> nObjects_rng(1,100);
  unsigned nObjects = nObjects_rng(rng);

  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",1);
  tray.AddModule("I3Muxer","muxer");
  tray.AddModule("I3TestSource<I3DOMLaunch>","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("I3TestSourceTestModule","test_module")
    ("MapName","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}

TEST(multiple_DOMLaunches_stress_test){

  I3Tray tray;

  boost::rand48 rng(static_cast<int>(time(0)));
  boost::uniform_smallint<unsigned> nObjects_rng(4000,4800);
  unsigned nObjects = nObjects_rng(rng);

  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",1);
  tray.AddModule("I3Muxer","muxer");
  tray.AddModule("I3TestSource<I3DOMLaunch>","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("I3TestSourceTestModule","test_module")
    ("MapName","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}