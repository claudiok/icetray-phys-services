#include <I3Test.h>

#include "root-icetray/RootI3Tray.h"

#include "phys-source/I3DummyPhysicsSource.h"
#include "phys-source/I3DummyCalibrationSource.h"
#include "phys-source/I3FileGeometrySource.h"
#include "phys-source/I3DummyDetectorStatusSource.h"
#include "phys-source/I3DummyMonitoringSource.h"

#include "FrameChecking.h"

#include "module-test/TestClientModule.h"

TEST_GROUP(FileGeometrySourceTest);

struct file_geo_source{};
typedef TestClientModule<file_geo_source> Client;

I3_MODULE(Client);

template<> template <>
inline void Client::CheckFrame<0>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Geometry","Frame is geometry frame");
  ENSURE(GeometryPresent(frame),"Frame contains geometry");
}

template<> template <>
inline void Client::CheckFrame<1>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Calibration","Frame is Calibration Frame");
  ENSURE(GeometryPresent(frame),"Frame contains Geometry");
  ENSURE(CalibrationPresent(frame),"Frame Contains Calibration");
}

template <> template <>
inline void Client::CheckFrame<2>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "DetectorStatus","Frame is status frame");
  ENSURE(GeometryPresent(frame),"Geometry present");
  ENSURE(CalibrationPresent(frame),"calibration present");
  ENSURE(DetectorStatusPresent(frame),"detector status present");
}

template <> template <>
inline void Client::CheckFrame<3>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Physics");
  ENSURE(GeometryPresent(frame));
  ENSURE(CalibrationPresent(frame));
  ENSURE(DetectorStatusPresent(frame));
  ENSURE(EventPresent(frame));
}

struct file_geo_source_print : public I3PhysicsModule
{
  file_geo_source_print(const I3Context& context) : I3PhysicsModule(context)
  {
    AddOutBox("OutBox");
  }
  void Physics(I3Frame& frame){cout<<GetEvent(frame)<<endl;}
  void DetectorStatus(I3Frame& frame){cout<<GetDetectorStatus(frame)<<endl;}
  void Geometry(I3Frame& frame){cout<<GetGeometry(frame)<<endl;}
  void Calibration(I3Frame& frame){cout<<GetCalibration(frame)<<endl;}

};

I3_MODULE(file_geo_source_print);

TEST(file_geo_source)
{
  ENSURE(getenv("I3_WORK"));
  string amandaFile(getenv("I3_WORK"));
  amandaFile.append("/phys-services/resources/amanda.geo");
  string icecubeFile(getenv("I3_WORK"));
  icecubeFile.append("/phys-services/resources/icecube.geo");

  RootI3Tray tray;
  
  tray.AddModule("I3DummyPhysicsSource","eventssource");
  tray.AddModule("I3DummyDetectorStatusSource","statussource");
  tray.AddModule("I3DummyCalibrationSource","calibsource");
  tray.AddModule("I3FileGeometrySource","geomsource");
  tray.SetParameter("geomsource","AmandaGeoFile",amandaFile);
  tray.SetParameter("geomsource","IceCubeGeoFile",icecubeFile);
  tray.AddModule("file_geo_source_print","print");
  tray.AddModule("Client","client");
  
  tray.ConnectBoxes("eventssource","OutBox","statussource");
  tray.ConnectBoxes("statussource","OutBox","calibsource");
  tray.ConnectBoxes("calibsource","OutBox","geomsource");
  tray.ConnectBoxes("geomsource","OutBox","print");
  tray.ConnectBoxes("print","OutBox","client");
  
  tray.Execute();
  tray.Finish();
}
