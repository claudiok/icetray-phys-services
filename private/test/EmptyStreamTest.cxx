#include <I3Test.h>

#include "root-icetray/RootI3Tray.h"

#include "phys-services/source/I3Muxer.h"
#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"

#include "FrameChecking.h"

#include "icetray/module-test/TestClientModule.h"

// This is a test that checks that each of the frames that comes
// through is a.) created on the right stream and b.) has the 
// right classes in it.
TEST_GROUP(EmptyStreamTest);

struct ev_stat_cal_geo{};
typedef TestClientModule<ev_stat_cal_geo> EvStatCalGeoClient;

I3_MODULE(EvStatCalGeoClient);

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

  tray.AddService<I3EmptyStreamsFactory>("empty")
    ("NFrames",5);
  
  tray.AddModule<I3Muxer>("muxme");

  tray.AddModule<EvStatCalGeoClient>("client");
  
  tray.Execute();
  tray.Finish();
}

struct ev_cal_geo{};
typedef TestClientModule<ev_cal_geo> EvCalGeoClient;

I3_MODULE(EvCalGeoClient);

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

  tray.AddService<I3EmptyStreamsFactory>("empty")
    ("NFrames",5);
  
  tray.AddModule<I3Muxer>("muxme");

  tray.AddModule<EvCalGeoClient>("client");
  
  tray.Execute();
  tray.Finish();
}
