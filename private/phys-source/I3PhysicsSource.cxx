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
  log_debug("Entering I3PhysicsSource::Process()");
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

I3EventOrigin& I3PhysicsSource::GetEventFactory()
{
  return 
    I3ContextAccess<I3EventOrigin>::GetService(GetContext(),
						I3EventOrigin::DefaultName());
}

I3GeometryOrigin& I3PhysicsSource::GetGeometryFactory()
{
  return I3ContextAccess<I3GeometryOrigin>::
    GetService(GetContext(),
	       I3GeometryOrigin::DefaultName());
}

I3CalibrationOrigin& I3PhysicsSource::GetCalibrationFactory()
{
  return I3ContextAccess<I3CalibrationOrigin>::
    GetService(GetContext(),
	       I3CalibrationOrigin::DefaultName());
}

void I3PhysicsSource::SendEvent()
{
  log_debug("Entering I3PhysicsSource::SendEvent()");
  currentEvent_ = GetEventFactory().PopEvent();
  assert(currentEvent_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Physics"));
  SendAll(frame);
}

void I3PhysicsSource::SendCalibration()
{
  log_debug("Entering I3PhysicsSource::SendCalibration()");
  Time nextEvent = GetEventFactory().NextEventTime();
  currentCalibration_ = GetCalibrationFactory().GetCalibration(nextEvent);
  currentCalibrationRange_ 
    = GetCalibrationFactory().GetCalibrationValidityRange(nextEvent);
  assert(currentCalibration_);
  assert(currentGeometryRange_.lower < currentGeometryRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Calibration"));
  SendAll(frame);
}

void I3PhysicsSource::SendGeometry()
{
  log_debug("Entering I3PhysicsSource::SendGeometry()");
  Time nextEvent = GetEventFactory().NextEventTime();
  currentGeometry_ = GetGeometryFactory().GetGeometry(nextEvent);
  currentGeometryRange_ = 
    GetGeometryFactory().GetGeometryValidityRange(nextEvent);
  assert(currentGeometry_);
  assert(currentGeometryRange_.lower < currentGeometryRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Geometry"));
  SendAll(frame);
}

void I3PhysicsSource::SendAll(I3Frame& frame)
{
  log_debug("Entering I3PhysicsSource::SendAll()");
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
  if(!IsGeometryCurrent(eventTime))
    return GEOMETRY;
  if(!IsCalibrationCurrent(eventTime))
    return CALIBRATION;
  return EVENT;
}

bool I3PhysicsSource::IsGeometryCurrent(Time time)
{
  if(!currentGeometry_)
    {
      log_debug("Geometry isn't current 'cause it hasn't been issued yet")
      return false;
    }
  log_debug("Next event time: %f and the current Geometry Range: %s",
	    time,
	    currentGeometryRange_.ToString().c_str())
  if(currentGeometryRange_.lower < time && currentGeometryRange_.upper > time)
    {
      log_debug("Geometry is current, no worries");
      return true;
    }
  log_debug("Calibration needs updating.");
  return false;
}

bool I3PhysicsSource::IsCalibrationCurrent(Time time)
{
  if(!currentCalibration_)
    {
      log_debug("Calibration isn't current 'cause it hasn't been issued yet");
      return false;
    }
  log_debug("Next event time: %f and the current Calibration Range: %s",
	    time,
	    currentCalibrationRange_.ToString().c_str())
  if(currentCalibrationRange_.lower < time &&
     currentCalibrationRange_.upper > time)
    {
      log_debug("Calibration is current, no worries!");
      return true;
    }
  log_debug("Calibration needs updating");
  return false;
}
