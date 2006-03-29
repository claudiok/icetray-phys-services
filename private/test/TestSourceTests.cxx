#include <I3Test.h>
#include "icetray/I3Tray.h"
#include "icetray/modules/TrashCan.h"
#include "phys-services/test-source/I3TestSourceTestModule.h"
#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"
#include "phys-services/source/I3Muxer.h"

#include "boost/random.hpp"

TEST_GROUP(I3TestSource);

TEST(multiple_MCHits){

  I3Tray tray;

  boost::rand48 rng(static_cast<int>(time(0)));
  boost::uniform_smallint<unsigned> nObjects_rng(1,100);
  unsigned nObjects = nObjects_rng(rng);

  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",1);
  tray.AddModule("I3Muxer","muxer");
  tray.AddModule("I3TestSource<I3MCHit>","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("I3TestSourceTestModule<I3MCHit>","test_module")
    ("MapName","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}

TEST(multiple_MCHits_stress_test){

  I3Tray tray;

  boost::rand48 rng(static_cast<int>(time(0)));
  boost::uniform_smallint<unsigned> nObjects_rng(400,1000);
  unsigned nObjects = nObjects_rng(rng);

  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",1);
  tray.AddModule("I3Muxer","muxer");
  tray.AddModule("I3TestSource<I3MCHit>","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("I3TestSourceTestModule<I3MCHit>","test_module")
    ("MapName","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}

TEST(multiple_MCHits_super_stress_test){

  I3Tray tray;

  boost::rand48 rng(static_cast<int>(time(0)));
  boost::uniform_smallint<unsigned> nObjects_rng(4400,4800);
  unsigned nObjects = nObjects_rng(rng);

  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",10);
  tray.AddModule("I3Muxer","muxer");
  tray.AddModule("I3TestSource<I3MCHit>","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("I3TestSourceTestModule<I3MCHit>","test_module")
    ("MapName","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}
