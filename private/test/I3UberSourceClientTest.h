#ifndef I3PHYSICSSOURCECLIENTTEST_H
#define I3PHYSICSSOURCECLIENTTEST_H

#include "phys-services/I3PhysicsModule.h"
#include "TUT/tut.h"
#include <iostream>

using namespace std;

class I3UberSourceClientTest : public I3PhysicsModule
{
 public:
  I3UberSourceClientTest(I3Context& context) : I3PhysicsModule(context)
    {
      AddOutBox("OutBox");
    }

  void Geometry(I3Frame& frame)
    {
      tut::ensure("geometry frame has geometry",
		  HasGeometry(frame));
      tut::ensure("geometry frame has geometry header",
		  HasGeometryHeader(frame));
      cout<<GetGeometryHeader(frame)<<endl;
      cout<<GetGeometry(frame)<<endl;
      PushFrame(frame,"OutBox");
    }
  void Physics(I3Frame& frame)
    {
      tut::ensure("event frame has geometry",
		  HasGeometry(frame));
      tut::ensure("event frame has geometry header",
		  HasGeometryHeader(frame));
      tut::ensure("event frame has calibration",
		  HasCalibration(frame));
      tut::ensure("event frame has calibration header",
		  HasCalibrationHeader(frame));
      tut::ensure("event frame has event",
		  HasEvent(frame));
      tut::ensure("event frame has event header",
		  HasEventHeader(frame));
      cout<<GetEventHeader(frame)<<endl;
      cout<<GetEvent(frame)<<endl;
      PushFrame(frame,"OutBox");
    }
  void Calibration(I3Frame& frame)
    {
      tut::ensure("Calibration frame has geometry",
		  HasGeometry(frame));
      tut::ensure("Calibration frame has geometry header",
		  HasGeometryHeader(frame));
      tut::ensure("calibration frame has calibration",
		  HasCalibration(frame));
      tut::ensure("calibration frame has calibration header",
		  HasCalibrationHeader(frame));
      cout<<GetCalibrationHeader(frame)<<endl;
      cout<<GetCalibration(frame)<<endl;
      PushFrame(frame,"OutBox");
    }
};

#endif
