#include "TUT/tut.h"

#include "phys-source/I3GeometryOrigin.h"
#include "phys-source/I3EventOrigin.h"
#include "phys-source/I3CalibrationOrigin.h"
#include "root-icetray/RootI3Tray.h"
#include "phys-source/I3PhysicsSource.h"
#include "I3PhysicsSourceClientTest.h"
#include "phys-source/I3DummyEventOriginFactory.h"
#include "phys-source/I3FileGeoOriginFactory.h"
#include "phys-source/I3DummyCalibOriginFactory.h"

namespace tut
{
  struct FileGeoOriginTest
  {
  };


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

    tray.AddModule<I3PhysicsSource>("source");
    tray.AddModule<I3PhysicsSourceClientTest>("client");

    tray.ConnectBoxes("source","OutBox","client");

    tray.Execute();
    tray.Finish();
  }
}
