#include <I3Test.h>

#include "root-icetray/RootI3Tray.h"

#include "phys-source/I3DummyPhysicsSource.h"
#include "phys-source/I3DummyCalibrationSource.h"
#include "phys-source/I3DummyGeometrySource.h"
#include "phys-source/I3DummyDetectorStatusSource.h"
#include "phys-source/I3DummyMonitoringSource.h"

#include "FrameChecking.h"

#include "module-test/TestClientModule.h"

TEST_GROUP(DummySourceTest);

struct ev_stat_cal_geo{};
typedef TestClientModule<ev_stat_cal_geo> EvStatCalGeoClient;

template<> template <>
inline void EvStatCalGeoClient::CheckFrame<0>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Geometry","Frame is geometry frame");
  ENSURE(GeometryPresent(frame),"Frame contains geometry");
}

template<> template <>
inline void EvStatCalGeoClient::CheckFrame<1>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Calibration","Frame is Calibration Frame");
  ENSURE(GeometryPresent(frame),"Frame contains Geometry");
  ENSURE(CalibrationPresent(frame),"Frame Contains Calibration");
}

template <> template <>
inline void EvStatCalGeoClient::CheckFrame<2>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "DetectorStatus","Frame is status frame");
  ENSURE(GeometryPresent(frame),"Geometry present");
  ENSURE(CalibrationPresent(frame),"calibration present");
  ENSURE(DetectorStatusPresent(frame),"detector status present");
}

template <> template <>
inline void EvStatCalGeoClient::CheckFrame<3>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Physics");
  ENSURE(GeometryPresent(frame));
  ENSURE(CalibrationPresent(frame));
  ENSURE(DetectorStatusPresent(frame));
  ENSURE(EventPresent(frame));
}


TEST(ev_stat_cal_geo)
{
  RootI3Tray tray;
  
  tray.AddModule<I3DummyPhysicsSource>("eventssource");
  tray.AddModule<I3DummyDetectorStatusSource>("statussource");
  tray.AddModule<I3DummyCalibrationSource>("calibsource");
  tray.AddModule<I3DummyGeometrySource>("geomsource");
  tray.AddModule<EvStatCalGeoClient>("client");
  
  tray.ConnectBoxes("eventssource","OutBox","statussource");
  tray.ConnectBoxes("statussource","OutBox","calibsource");
  tray.ConnectBoxes("calibsource","OutBox","geomsource");
  tray.ConnectBoxes("geomsource","OutBox","client");
  
  tray.Execute();
  tray.Finish();
}

struct ev_cal_geo{};
typedef TestClientModule<ev_cal_geo> EvCalGeoClient;

template<> template <>
inline void EvCalGeoClient::CheckFrame<0>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Geometry");
  ENSURE(GeometryPresent(frame));
}

template<> template <>
inline void EvCalGeoClient::CheckFrame<1>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Calibration");
  ENSURE(GeometryPresent(frame));
  ENSURE(CalibrationPresent(frame));
}

template <> template <>
inline void EvCalGeoClient::CheckFrame<2>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Physics");
  ENSURE(GeometryPresent(frame));
  ENSURE(CalibrationPresent(frame));
  ENSURE(EventPresent(frame));
}

TEST(ev_cal_geo)
{
  RootI3Tray tray;
  
  tray.AddModule<I3DummyPhysicsSource>("eventssource");
  tray.AddModule<I3DummyCalibrationSource>("calibsource");
  tray.AddModule<I3DummyGeometrySource>("geomsource");
  tray.AddModule<EvCalGeoClient>("client");
  
  tray.ConnectBoxes("eventssource","OutBox","calibsource");
  tray.ConnectBoxes("calibsource","OutBox","geomsource");
  tray.ConnectBoxes("geomsource","OutBox","client");
  
  tray.Execute();
  tray.Finish();
}

struct mon_stat_cal_geo{};
typedef TestClientModule<mon_stat_cal_geo> MonStatCalGeoClient;

template<> template <>
inline void MonStatCalGeoClient::CheckFrame<0>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Geometry","Frame is geometry frame");
  ENSURE(GeometryPresent(frame),"Frame contains geometry");
}

template<> template <>
inline void MonStatCalGeoClient::CheckFrame<1>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Calibration","Frame is Calibration Frame");
  ENSURE(GeometryPresent(frame),"Frame contains Geometry");
  ENSURE(CalibrationPresent(frame),"Frame Contains Calibration");
}

template <> template <>
inline void MonStatCalGeoClient::CheckFrame<2>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "DetectorStatus","Frame is status frame");
  ENSURE(GeometryPresent(frame),"Geometry present");
  ENSURE(CalibrationPresent(frame),"calibration present");
  ENSURE(DetectorStatusPresent(frame),"detector status present");
}

template <> template <>
inline void MonStatCalGeoClient::CheckFrame<3>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Monitor");
  ENSURE(GeometryPresent(frame));
  ENSURE(CalibrationPresent(frame));
  ENSURE(DetectorStatusPresent(frame));
  ENSURE(MonitoringPresent(frame));
}


TEST(mon_stat_cal_geo)
{
  RootI3Tray tray;
  
  tray.AddModule<I3DummyMonitoringSource>("eventssource");
  tray.AddModule<I3DummyDetectorStatusSource>("statussource");
  tray.AddModule<I3DummyCalibrationSource>("calibsource");
  tray.AddModule<I3DummyGeometrySource>("geomsource");
  tray.AddModule<MonStatCalGeoClient>("client");
  
  tray.ConnectBoxes("eventssource","OutBox","statussource");
  tray.ConnectBoxes("statussource","OutBox","calibsource");
  tray.ConnectBoxes("calibsource","OutBox","geomsource");
  tray.ConnectBoxes("geomsource","OutBox","client");
  
  tray.Execute();
  tray.Finish();
}

struct mon_cal_geo{};
typedef TestClientModule<mon_cal_geo> MonCalGeoClient;

template<> template <>
inline void MonCalGeoClient::CheckFrame<0>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Geometry");
  ENSURE(GeometryPresent(frame));
}

template<> template <>
inline void MonCalGeoClient::CheckFrame<1>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Calibration");
  ENSURE(GeometryPresent(frame));
  ENSURE(CalibrationPresent(frame));
}

template <> template <>
inline void MonCalGeoClient::CheckFrame<2>(I3Frame& frame)
{
  ENSURE(DumpStop(frame) == "Monitor");
  ENSURE(GeometryPresent(frame));
  ENSURE(CalibrationPresent(frame));
  ENSURE(MonitoringPresent(frame));
}

TEST(mon_cal_geo)
{
  RootI3Tray tray;
  
  tray.AddModule<I3DummyMonitoringSource>("eventssource");
  tray.AddModule<I3DummyCalibrationSource>("calibsource");
  tray.AddModule<I3DummyGeometrySource>("geomsource");
  tray.AddModule<MonCalGeoClient>("client");
  
  tray.ConnectBoxes("eventssource","OutBox","calibsource");
  tray.ConnectBoxes("calibsource","OutBox","geomsource");
  tray.ConnectBoxes("geomsource","OutBox","client");
  
  tray.Execute();
  tray.Finish();
}
