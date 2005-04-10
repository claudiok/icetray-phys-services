#include "TUT/tut.h"

#include "module-test/TestClientModule.h"

struct DummyFactoryClient
{
};


typedef TestClientModule<DummyFactoryClient> Client;

template<> template<>
inline void Client::CheckFrame<0>(I3Frame& frame)
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

inline void Client::CheckFrame<1>(I3Frame& frame)
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

inline void Client::CheckFrame<2>(I3Frame& frame)
{
  tut::ensure("detector status frame has geometry",
	      I3FrameAccess<I3Geometry>::Exists(frame,
						"Geometry"));
  tut::ensure("detector status frame has geometry header",
	      I3FrameAccess<I3GeometryHeader>::Exists(frame,
						      "GeometryHeader"));
  tut::ensure("detector status frame has detector status",
	      I3FrameAccess<I3DetectorStatus>::
	      Exists(frame,"DetectorStatus"));
  tut::ensure("detector status frame has detector status header",
	      I3FrameAccess<I3DetectorStatusHeader>::
	      Exists(frame,"DetectorStatus"));
  tut::ensure("detector status frame has calibration",
	      I3FrameAccess<I3Calibration>::Exists(frame,"Calibration"));
  tut::ensure("detector status frame has calibration header",
	      I3FrameAccess<I3CalibrationHeader>::
	      Exists(frame,
		     "CalibrationHeader"));
  
  cout<<I3FrameAccess<I3DetectorStatusHeader>::Get(frame,
						   "DetectorStatusHeader")
      <<endl;
  cout<<I3FrameAccess<I3DetectorStatus>::Get(frame,
					     "DetectorStatus")
      <<endl;
  
}



inline void Client::CheckFrame<3>(I3Frame& frame)
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

inline void Client::CheckFrame<4>(I3Frame& frame)
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
  tut::ensure("event frame has detector status",
	      I3FrameAccess<I3DetectorStatus>::
	      Exists(frame,"DetectorStatus"));
  tut::ensure("event frame has detector status header",
	      I3FrameAccess<I3DetectorStatusHeader>::
	      Exists(frame,"DetectorStatus"));
  tut::ensure("event frame has event",
	      I3FrameAccess<I3Event>::Exists(frame,"Physics"));
  tut::ensure("event frame has event header",
	      I3FrameAccess<I3EventHeader>::Exists(frame,"PhysicsHeader"));
  cout<<I3FrameAccess<I3EventHeader>::Get(frame,"PhysicsHeader")<<endl;
  cout<<I3FrameAccess<I3Event>::Get(frame,"Physics")<<endl;
}
