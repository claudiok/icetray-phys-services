#include "TUT/tut.h"

#include "phys-source/I3GeometryOrigin.h"
#include "phys-source/I3MonitoringOrigin.h"
#include "phys-source/I3CalibrationOrigin.h"
#include "phys-source/I3DetectorStatusOrigin.h"

#include "root-icetray/RootI3Tray.h"

#include "phys-source/I3UberSource_Monitoring.h"

#include "phys-source/I3DummyMonitoringOriginFactory.h"
#include "phys-source/I3DummyGeoOriginFactory.h"
#include "phys-source/I3DummyCalibOriginFactory.h"
#include "phys-source/I3DummyDetectorStatusOriginFactory.h"

#include "phys-source/I3PhysicsSource.h"
#include "phys-source/I3CalibrationSource.h"
#include "phys-source/I3GeometrySource.h"
#include "phys-source/I3DetectorStatusSource.h"

#include "SimpleOrderingTest-Monitoring.h"

namespace tut
{
  struct DummyMonitoringFactoryTest
  {
  };

  typedef test_group<DummyMonitoringFactoryTest> factory;
  typedef factory::object object;
}

namespace
{
  static tut::factory dummyFactoryTestFactory("DummyMonitoringFactoryTest");
}

namespace tut
{
  template<> template<>
  void object::test<1>() 
  {
    RootI3Tray tray;
 
    tray.AddService<I3DummyMonitoringOriginFactory>("events");
    tray.AddService<I3DummyDetectorStatusOriginFactory>("status");
    tray.AddService<I3DummyGeoOriginFactory>("geo");
    tray.AddService<I3DummyCalibOriginFactory>("calib");

    tray.AddModule<I3UberSource_Monitoring>("source");
    tray.AddModule<Client>("client");

    tray.ConnectBoxes("source","OutBox","client");

    tray.Execute();
    tray.Finish();
  }

//   template<> template<>
//   void object::test<2>() 
//   {
//     RootI3Tray tray;
 
//     tray.AddService<I3DummyMonitoringOriginFactory>("events");
//     tray.AddService<I3DummyDetectorStatusOriginFactory>("status");
//     tray.AddService<I3DummyGeoOriginFactory>("geo");
//     tray.AddService<I3DummyCalibOriginFactory>("calib");

//     tray.AddModule<I3PhysicsSource>("eventssource");
//     tray.AddModule<I3DetectorStatusSource>("statussource");
//     tray.AddModule<I3CalibrationSource>("calibsource");
//     tray.AddModule<I3GeometrySource>("geomsource");
//     tray.AddModule<Client>("client");

//     tray.ConnectBoxes("eventssource","OutBox","statussource");
//     tray.ConnectBoxes("statussource","OutBox","calibsource");
//     tray.ConnectBoxes("calibsource","OutBox","geomsource");
//     tray.ConnectBoxes("geomsource","OutBox","client");

//     tray.Execute();
//     tray.Finish();
//   }

}



