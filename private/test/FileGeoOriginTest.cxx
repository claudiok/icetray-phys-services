#include "TUT/tut.h"

#include "phys-source/I3GeometryOrigin.h"
#include "phys-source/I3EventOrigin.h"
#include "phys-source/I3CalibrationOrigin.h"
#include "root-icetray/RootI3Tray.h"
#include "phys-source/I3UberSource.h"
#include "phys-source/I3DummyEventOriginFactory.h"
#include "phys-source/I3FileGeoOriginFactory.h"
#include "phys-source/I3DummyCalibOriginFactory.h"

#include "module-test/TestClientModule.h"

namespace tut
{
  struct FileGeoOriginTest
  {
  };


  struct FileGeoOriginTester
  {

  };

  typedef TestClientModule<FileGeoOriginTester> Client;

  typedef test_group<FileGeoOriginTest> factory;
  typedef factory::object object;
}

namespace
{
  static tut::factory t("FileGeoOriginTest");
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
    tut::ensure("calibration frame has geometry",
		I3FrameAccess<I3Geometry>::Exists(frame,
						  "Geometry"));
    tut::ensure("calibration frame has geometry header",
		I3FrameAccess<I3GeometryHeader>::Exists(frame,
							"GeometryHeader"));
    cout<<I3FrameAccess<I3CalibrationHeader>::Get(frame,
						  "CalibrationHeader")
	<<endl;
    cout<<I3FrameAccess<I3Calibration>::Get(frame,
					    "Calibration")
	<<endl;
  }

  void Client::CheckFrame<2>(I3Frame& frame)
  {
    tut::ensure("event frame has geometry",
		I3FrameAccess<I3Geometry>::Exists(frame,"Geometry"));
    tut::ensure("event frame has geometry header",
		I3FrameAccess<I3GeometryHeader>::
		Exists(frame,"GeometryHeader"));
    tut::ensure("event frame has calibration",
		I3FrameAccess<I3Calibration>::Exists(frame,
						     "Calibration"));
    tut::ensure("event frame has calibration header",
		I3FrameAccess<I3CalibrationHeader>
		::Exists(frame,
			 "CalibrationHeader"));
    tut::ensure("event frame has event",
		I3FrameAccess<I3Event>::Exists(frame,"Physics"));
    tut::ensure("event frame has event header",
		I3FrameAccess<I3EventHeader>::Exists(frame,"PhysicsHeader"));
    cout<<I3FrameAccess<I3EventHeader>::Get(frame,"PhysicsHeader")<<endl;
    cout<<I3FrameAccess<I3Event>::Get(frame,"Physics")<<endl;
    
  }
  
  void Client::CheckFrame<3>(I3Frame& frame)
  {
    tut::ensure("event frame has geometry",
		I3FrameAccess<I3Geometry>::Exists(frame,"Geometry"));
    tut::ensure("event frame has geometry header",
		I3FrameAccess<I3GeometryHeader>::
		Exists(frame,"GeometryHeader"));
    tut::ensure("event frame has calibration",
		I3FrameAccess<I3Calibration>::Exists(frame,"Calibration"));
    tut::ensure("event frame has calibration header",
		I3FrameAccess<I3CalibrationHeader>::
		Exists(frame,
		       "CalibrationHeader"));
    
    tut::ensure("event frame has event",
		I3FrameAccess<I3Event>::Exists(frame,"Physics"));
    tut::ensure("event frame has event header",
		I3FrameAccess<I3EventHeader>::Exists(frame,"PhysicsHeader"));
    cout<<I3FrameAccess<I3EventHeader>::Get(frame,"PhysicsHeader")<<endl;
    cout<<I3FrameAccess<I3Event>::Get(frame,"Physics")<<endl;
  }


  template<> template<>
  void object::test<1>() 
  {
    RootI3Tray tray;
 
    ensure(getenv("I3_WORK"));
    string amandaFile(getenv("I3_WORK"));
    amandaFile.append("/phys-services/resources/amanda.geo");
    string icecubeFile(getenv("I3_WORK"));
    icecubeFile.append("/phys-services/resources/icecube.geo");
    
    tray.AddService<I3DummyEventOriginFactory>("events");

    tray.AddService<I3FileGeoOriginFactory>("geo");
    tray.SetParameter("geo","AmandaGeoFile",amandaFile);
    tray.SetParameter("geo","IceCubeGeoFile",icecubeFile);
    
    tray.AddService<I3DummyCalibOriginFactory>("calib");

    tray.AddModule<I3UberSource>("source");
    tray.AddModule<Client>("client");

    tray.ConnectBoxes("source","OutBox","client");

    tray.Execute();
    tray.Finish();
  }
}

