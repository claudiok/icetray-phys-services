#include "TUT/tut.h"

#include "phys-source/I3GeometryOrigin.h"
#include "phys-source/I3EventOrigin.h"
#include "phys-source/I3CalibrationOrigin.h"
#include "root-icetray/RootI3Tray.h"
#include "phys-source/I3PhysicsSource.h"
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
    tray.AddModule<I3PhysicsSource>("source");
    tray.AddModule<I3PhysicsSourceClientTest>("client");

    tray.ConnectBoxes("source","OutBox","client");

    tray.Execute();
    tray.Finish();
  }
}

