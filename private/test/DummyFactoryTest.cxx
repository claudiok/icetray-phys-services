#include "TUT/tut.h"

#include "phys-source/I3GeometryOrigin.h"
#include "phys-source/I3EventOrigin.h"
#include "phys-source/I3CalibrationOrigin.h"

#include "root-icetray/RootI3Tray.h"

#include "phys-source/I3UberSource.h"
#include "I3UberSourceClientTest.h"

#include "phys-source/I3DummyEventOriginFactory.h"
#include "phys-source/I3DummyGeoOriginFactory.h"
#include "phys-source/I3DummyCalibOriginFactory.h"

#include "phys-source/I3PhysicsSource.h"
#include "phys-source/I3CalibrationSource.h"
#include "phys-source/I3GeometrySource.h"

#include "module-test/TestClientModule.h"

namespace tut
{
  struct DummyFactoryTest
  {
  };

  struct DummyFactoryClient
  {
  };

  typedef test_group<DummyFactoryTest> factory;
  typedef factory::object object;
  typedef TestClientModule<DummyFactoryClient> Client;
}

namespace
{
  static tut::factory t("DummyFactoryTest");
}

namespace tut
{
  template<> template<>
  void Client::CheckFrame<0>(I3Frame& frame)
  {
    tut::ensure("geometry frame has geometry",
		I3FrameAccess<I3Geometry>::Exists(frame,
						  "Geometry"));
    tut::ensure("geometry frame has geometry header",
		I3FrameAccess<I3GeometryHeader>::Exists(frame,
							"GeometryHeader"));
    cout<<I3FrameAccess<I3GeometryHeader>::Get(frame,"GeometryHeader")<<endl;
    cout<<I3FrameAccess<I3GeometryHeader>::Get(frame,"Geometry")<<endl;
  }

  void Client::CheckFrame<1>(I3Frame& frame)
  {
    tut::ensure("calibration frame has calibration",
		I3FrameAccess<I3Calibration>::Exists(frame,"Calibration"));
    tut::ensure("calibration frame has calibration header",
		I3FrameAccess<I3CalibrationHeader>::
		Exists(frame,
		       "CalibrationHeader"));
    cout<<I3FrameAccess<I3CalibrationHeader>::Get(frame,
						  "CalibrationHeader")
	<<endl;
    cout<<I3FrameAccess<I3Calibration>::Get(frame,
					    "Calibration")
	<<endl;
  }

  void Client::CheckFrame<2>(I3Frame& frame)
  {
//       tut::ensure("event frame has geometry",
// 		  HasGeometry(frame));
//       tut::ensure("event frame has geometry header",
// 		  HasGeometryHeader(frame));
    tut::ensure("event frame has calibration",
		I3FrameAccess<I3Calibration>::Exists(frame,
						     "Calibration"));
    tut::ensure("event frame has calibration header",
		I3FrameAccess<I3CalibrationHeader>::Exists(frame,
							   "CalibrationHeader"));
    //       tut::ensure("event frame has event",
		   // 		  HasEvent(frame));
//       tut::ensure("event frame has event header",
// 		  HasEventHeader(frame));
//       cout<<GetEventHeader(frame)<<endl;
//       cout<<GetEvent(frame)<<endl;
  }

  void Client::CheckFrame<3>(I3Frame& frame)
  {
//       tut::ensure("event frame has geometry",
// 		  HasGeometry(frame));
//       tut::ensure("event frame has geometry header",
// 		  HasGeometryHeader(frame));
    tut::ensure("event frame has calibration",
		I3FrameAccess<I3Calibration>::Exists(frame,"Calibration"));
    tut::ensure("event frame has calibration header",
		I3FrameAccess<I3CalibrationHeader>::Exists(frame,
							   "CalibrationHeader"));
//       tut::ensure("event frame has event",
// 		  HasEvent(frame));
//       tut::ensure("event frame has event header",
// 		  HasEventHeader(frame));
//       cout<<GetEventHeader(frame)<<endl;
//       cout<<GetEvent(frame)<<endl;
  }


  template<> template<>
  void object::test<1>() 
  {
    RootI3Tray tray;
 
    tray.AddService<I3DummyEventOriginFactory>("events");
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
 
    tray.AddService<I3DummyEventOriginFactory>("events");
    tray.AddService<I3DummyGeoOriginFactory>("geo");
    tray.AddService<I3DummyCalibOriginFactory>("calib");

    tray.AddModule<I3PhysicsSource>("eventssource");
    tray.AddModule<I3CalibrationSource>("calibsource");
    tray.AddModule<I3GeometrySource>("geomsource");
    tray.AddModule<Client>("client");

    tray.ConnectBoxes("eventssource","OutBox","calibsource");
    tray.ConnectBoxes("calibsource","OutBox","geomsource");
    tray.ConnectBoxes("geomsource","OutBox","client");

    tray.Execute();
    tray.Finish();
  }

}



