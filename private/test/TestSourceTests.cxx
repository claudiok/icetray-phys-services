#include <I3Test.h>
#include "icetray/I3Tray.h"
#include "icetray/modules/TrashCan.h"
#include "phys-services/test-source/I3TestSourceTestModule.h"
#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"
#include "phys-services/source/I3Muxer.h"

#include "boost/random.hpp"

#include "phys-services/test-source/I3TestSource.h"
#include "dataclasses/I3Vector.h"
#include "dataclasses/physics/I3AMANDAAnalogReadout.h"
#include "dataclasses/physics/I3DOMLaunch.h"
#include "dataclasses/physics/I3MCHit.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/physics/I3TWRLaunch.h"

template <> void I3TestSource<I3AMANDAAnalogReadout>::Randomize(I3AMANDAAnalogReadout& p){};
template <> void I3TestSource<I3DOMLaunch>::Randomize(I3DOMLaunch& p){};
template <> void I3TestSource<I3TWRLaunch>::Randomize(I3TWRLaunch& p){};
template <> void I3TestSource<I3Vector<I3MCHit> >::Randomize(I3Vector<I3MCHit>& p){};
template <> void I3TestSource<I3Vector<I3RecoHit> >::Randomize(I3Vector<I3RecoHit>& p){};
template <> void I3TestSource<I3Vector<I3RecoPulse> >::Randomize(I3Vector<I3RecoPulse>& p){};

template class I3TestSource<I3AMANDAAnalogReadout>;
template class I3TestSource<I3DOMLaunch>;
template class I3TestSource<I3TWRLaunch>;
template class I3TestSource<I3Vector<I3MCHit> >;
template class I3TestSource<I3Vector<I3RecoHit> >;
template class I3TestSource<I3Vector<I3RecoPulse> >;

I3_MODULE(I3TestSource<I3AMANDAAnalogReadout>);
I3_MODULE(I3TestSource<I3DOMLaunch>);
I3_MODULE(I3TestSource<I3TWRLaunch>);
I3_MODULE(I3TestSource<I3Vector<I3MCHit> >);
I3_MODULE(I3TestSource<I3Vector<I3RecoHit> >);
I3_MODULE(I3TestSource<I3Vector<I3RecoPulse> >);

template class I3TestSourceTestModule<I3AMANDAAnalogReadout>;
template class I3TestSourceTestModule<I3DOMLaunch>;
template class I3TestSourceTestModule<I3Vector<I3MCHit> >;
template class I3TestSourceTestModule<I3Vector<I3RecoHit> >;
template class I3TestSourceTestModule<I3Vector<I3RecoPulse> >;
template class I3TestSourceTestModule<I3TWRLaunch>;

I3_MODULE(I3TestSourceTestModule<I3AMANDAAnalogReadout>);
I3_MODULE(I3TestSourceTestModule<I3DOMLaunch>);
I3_MODULE(I3TestSourceTestModule<I3Vector<I3MCHit> >);
I3_MODULE(I3TestSourceTestModule<I3Vector<I3RecoHit> >);
I3_MODULE(I3TestSourceTestModule<I3Vector<I3RecoPulse> >);
I3_MODULE(I3TestSourceTestModule<I3TWRLaunch>);


TEST_GROUP(I3TestSource);

TEST(multiple_MCHits){

  I3Tray tray;

  boost::rand48 rng(static_cast<int>(time(0)));
  boost::uniform_smallint<unsigned> nObjects_rng(1,100);
  unsigned nObjects = nObjects_rng(rng);

  tray.AddService("I3EmptyStreamsFactory","empty_streams")
    ("NFrames",1);
  tray.AddModule("I3Muxer","muxer");
  tray.AddModule("I3TestSource<I3Vector<I3MCHit> >","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("I3TestSourceTestModule<I3Vector<I3MCHit> >","test_module")
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
  tray.AddModule("I3TestSource<I3Vector<I3MCHit> >","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("I3TestSourceTestModule<I3Vector<I3MCHit> >","test_module")
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
  tray.AddModule("I3TestSource<I3Vector<I3MCHit> >","test_source")
    ("OutputMap","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("I3TestSourceTestModule<I3Vector<I3MCHit> >","test_module")
    ("MapName","ParticleMap")
    ("NObjects",nObjects);
  tray.AddModule("TrashCan","trash");

  tray.Execute();
  tray.Finish();
}
