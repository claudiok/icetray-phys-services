#ifndef I3PHYSICSSOURCECLIENTTEST_H
#define I3PHYSICSSOURCECLIENTTEST_H

#include "phys-services/I3PhysicsModule.h"
#include "TUT/tut.h"
#include <iostream>

using namespace std;

class I3PhysicsSourceClientTest : public I3PhysicsModule
{
 public:
  I3PhysicsSourceClientTest(I3Context& context) : I3PhysicsModule(context)
    {
      AddOutBox("OutBox");
    }

  void Geometry(I3Frame& frame)
    {
      tut::ensure(HasGeometry(frame));
      tut::ensure(HasGeometryHeader(frame));
      cout<<GetGeometryHeader(frame)<<endl;
      cout<<GetGeometry(frame)<<endl;
      PushFrame(frame,"OutBox");
    }
  void Physics(I3Frame& frame)
    {
      tut::ensure(HasGeometry(frame));
      tut::ensure(HasGeometryHeader(frame));
      tut::ensure(HasCalibration(frame));
      tut::ensure(HasCalibrationHeader(frame));
      tut::ensure(HasEvent(frame));
      tut::ensure(HasEventHeader(frame));
      cout<<GetEventHeader(frame)<<endl;
      cout<<GetEvent(frame)<<endl;
      PushFrame(frame,"OutBox");
    }
  void Calibration(I3Frame& frame)
    {
      tut::ensure(HasGeometry(frame));
      tut::ensure(HasGeometryHeader(frame));
      tut::ensure(HasCalibration(frame));
      tut::ensure(HasCalibrationHeader(frame));
      cout<<GetCalibrationHeader(frame)<<endl;
      cout<<GetCalibration(frame)<<endl;
      PushFrame(frame,"OutBox");
    }
};

#endif
