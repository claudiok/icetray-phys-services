#include "phys-source/I3PhysicsSource.h"
#include <map>

I3PhysicsSource::I3PhysicsSource(I3Context& context) : I3Source(context)
{
  AddOutBox("OutBox");
  NoActiveInBox();
  if(!I3Stream::StreamExists("Physics"))
    I3Stream::AddStream("Physics","Event Stream");
  if(!I3Stream::StreamExists("Geometry"))
    I3Stream::AddStream("Geometry","Geometry Stream");
  if(!I3Stream::StreamExists("Calibration"))
    I3Stream::AddStream("Calibration","Calibration Stream");
}

void I3PhysicsSource::Process()
{
  Stream next = NextStream();
  switch (next)
      {
      case EVENT:
	SendEvent();
	return;
      case GEOMETRY:
	SendGeometry();
	return;
      case CALIBRATION:
	SendCalibration();
	return;
      case NONE:
	RequestSuspension();
	return;
      default:
	Fatal("Something weird happened");
      }
}


void I3PhysicsSource::SendEvent()
{
  currentEvent_ = GetEventFactory().PopEvent();
  assert(currentEvent_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Physics"));
  SendAll(frame);
}

void I3PhysicsSource::SendCalibration()
{
  Time nextEvent = GetEventFactory().NextEventTime();
  currentCalibration_ = GetCalibrationFactory().GetCalibration(nextEvent);
  assert(currentCalibration_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Calibration"));
  SendAll(frame);
}

void I3PhysicsSource::SendGeometry()
{
  Time nextEvent = GetEventFactory().NextEventTime();
  currentGeometry_ = GetGeometryFactory().GetGeometry(nextEvent);
  assert(currentGeometry_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Geometry"));
  SendAll(frame);
}

void I3PhysicsSource::SendAll(I3Frame& frame)
{
  if(currentEvent_)
    {
      I3FrameAccess<I3Event>::Put(frame,
				  currentEvent_.event,
				  "Physics");
      I3FrameAccess<I3EventHeader>::Put(frame,
					currentEvent_.header,
					"PhysicsHeader");
    }
  if(currentGeometry_)
    {
      I3FrameAccess<I3Geometry>::Put(frame,
				     currentGeometry_.geometry,
				     "Geometry");
      I3FrameAccess<I3GeometryHeader>::Put(frame,
					   currentGeometry_.header,
					   "GeometryHeader");
    }
  if(currentCalibration_)
    {
      I3FrameAccess<I3Calibration>::Put(frame,
				     currentCalibration_.calibration,
				     "Calibration");
      I3FrameAccess<I3CalibrationHeader>::Put(frame,
					   currentCalibration_.header,
					   "CalibrationHeader");
    }

  PushFrame(frame,"OutBox");
}

I3PhysicsSource::Stream I3PhysicsSource::NextStream()
{
  if(!GetEventFactory().MoreEvents())
    return NONE;

  Time eventTime = GetEventFactory().NextEventTime();
  Time geoTime = GetGeometryFactory().NextGeometryTime();
  Time calibTime = GetCalibrationFactory().NextCalibrationTime();

  if(geoTime < eventTime)
    return GEOMETRY;
  if(calibTime < eventTime)
    return CALIBRATION;
  return EVENT;
}
