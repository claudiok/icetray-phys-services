#include <I3Test.h>

#include "module-test/TestClientModule.h"

#include "FrameChecking.h"

struct DummyFactoryClient
{
};


typedef TestClientModule<DummyFactoryClient> Client;

template<> template<>
inline void Client::CheckFrame<0>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "Geometry");
  ENSURE(GeometryPresent(frame));

  cout<<I3FrameAccess<I3GeometryHeader>::Get(frame,"GeometryHeader")<<endl;
  cout<<I3FrameAccess<I3GeometryHeader>::Get(frame,"Geometry")<<endl;
}

inline void Client::CheckFrame<1>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "Calibration");
  ENSURE(CalibrationPresent(frame));
  ENSURE(GeometryPresent(frame));

  cout<<I3FrameAccess<I3CalibrationHeader>::Get(frame,
						"CalibrationHeader")
      <<endl;
  cout<<I3FrameAccess<I3Calibration>::Get(frame,
					  "Calibration")
      <<endl;
}

inline void Client::CheckFrame<2>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "DetectorStatus");
  ENSURE(CalibrationPresent(frame));
  ENSURE(DetectorStatusPresent(frame));
  ENSURE(GeometryPresent(frame));
  
  cout<<I3FrameAccess<I3DetectorStatusHeader>::Get(frame,
						   "DetectorStatusHeader")
      <<endl;
  cout<<I3FrameAccess<I3DetectorStatus>::Get(frame,
					     "DetectorStatus")
      <<endl;
  
}



inline void Client::CheckFrame<3>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "Physics");

  ENSURE(CalibrationPresent(frame));
  ENSURE(DetectorStatusPresent(frame));
  ENSURE(GeometryPresent(frame));
  ENSURE(EventPresent(frame));

  cout<<I3FrameAccess<I3EventHeader>::Get(frame,"PhysicsHeader")<<endl;
  cout<<I3FrameAccess<I3Event>::Get(frame,"Physics")<<endl;

}

inline void Client::CheckFrame<4>(I3Frame& frame)
{
  log_debug("FrameStream: %s",DumpStop(frame).c_str());
  ENSURE(DumpStop(frame) == "Physics");

  ENSURE(CalibrationPresent(frame));
  ENSURE(DetectorStatusPresent(frame));
  ENSURE(GeometryPresent(frame));
  ENSURE(EventPresent(frame));

  cout<<I3FrameAccess<I3EventHeader>::Get(frame,"PhysicsHeader")<<endl;
  cout<<I3FrameAccess<I3Event>::Get(frame,"Physics")<<endl;
}
