#include "TUT/tut.h"

#include "phys-source/I3GeometryOrigin.h"
#include "phys-source/I3EventOrigin.h"
#include "phys-source/I3CalibrationOrigin.h"
#include "phys-source/I3DetectorStatusOrigin.h"

#include "root-icetray/RootI3Tray.h"

#include "phys-source/I3UberSource.h"

#include "phys-source/I3DummyEventOriginFactory.h"
#include "phys-source/I3DummyGeoOriginFactory.h"
#include "phys-source/I3DummyCalibOriginFactory.h"
#include "phys-source/I3DummyDetectorStatusOriginFactory.h"

#include "phys-source/I3DummyPhysicsSource.h"
#include "phys-source/I3DummyCalibrationSource.h"
#include "phys-source/I3DummyGeometrySource.h"
#include "phys-source/I3DummyDetectorStatusSource.h"

#include "SimpleOrderingTest.h"

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
  static tut::factory dummyFactoryTestFactory("DummyFactoryTest");
}

namespace tut
{
  template<> template<>
  void object::test<1>() 
  {
    RootI3Tray tray;
 
    tray.AddService<I3DummyEventOriginFactory>("events");
    tray.AddService<I3DummyDetectorStatusOriginFactory>("status");
    tray.AddService<I3DummyGeoOriginFactory>("geo");
    tray.AddService<I3DummyCalibOriginFactory>("calib");

    tray.AddModule<I3UberSource>("source");
    tray.AddModule<Client>("client");

    tray.ConnectBoxes("source","OutBox","client");

    tray.Execute();
    tray.Finish();
  }

  template<> template<>
  void object::test<2>() 
  {
    RootI3Tray tray;
 
    tray.AddModule<I3DummyPhysicsSource>("eventssource");
    tray.AddModule<I3DummyDetectorStatusSource>("statussource");
    tray.AddModule<I3DummyCalibrationSource>("calibsource");
    tray.AddModule<I3DummyGeometrySource>("geomsource");
    tray.AddModule<Client>("client");

    tray.ConnectBoxes("eventssource","OutBox","statussource");
    tray.ConnectBoxes("statussource","OutBox","calibsource");
    tray.ConnectBoxes("calibsource","OutBox","geomsource");
    tray.ConnectBoxes("geomsource","OutBox","client");

    tray.Execute();
    tray.Finish();
  }

}



