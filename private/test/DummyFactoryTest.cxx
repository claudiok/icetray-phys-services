#include "TUT/tut.h"

#include "phys-source/I3GeometryFactory.h"
#include "phys-source/I3EventFactory.h"
#include "phys-source/I3CalibrationFactory.h"
#include "DummyPhysicsSource.h"
#include "root-icetray/RootI3Tray.h"
#include "I3PhysicsSourceClientTest.h"

namespace tut
{
  struct DummyFactoryTest
  {
  };


  typedef test_group<DummyFactoryTest> factory;
  typedef factory::object object;
}

namespace
{
  static tut::factory t("DummyFactoryTest");
}

namespace tut
{
  template<> template<>
  void object::test<1>() 
  {
    RootI3Tray tray;
    tray.AddModule<DummyPhysicsSource>("source");
    tray.AddModule<I3PhysicsSourceClientTest>("client");

    tray.ConnectBoxes("source","OutBox","client");

    tray.Execute();
    tray.Finish();
  }
}

