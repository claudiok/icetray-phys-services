#include "phys-source/I3UberSource.h"
#include <map>

I3UberSource::I3UberSource(I3Context& context) : I3Source(context)
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

void I3UberSource::Process()
{
  log_debug("Entering I3UberSource::Process()");
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

I3EventOrigin& I3UberSource::GetEventFactory()
{
  return 
    I3ContextAccess<I3EventOrigin>::GetService(GetContext(),
						I3EventOrigin::DefaultName());
}

I3GeometryOrigin& I3UberSource::GetGeometryFactory()
{
  return I3ContextAccess<I3GeometryOrigin>::
    GetService(GetContext(),
	       I3GeometryOrigin::DefaultName());
}

I3CalibrationOrigin& I3UberSource::GetCalibrationFactory()
{
  return I3ContextAccess<I3CalibrationOrigin>::
    GetService(GetContext(),
	       I3CalibrationOrigin::DefaultName());
}

void I3UberSource::SendEvent()
{
  log_debug("Entering I3UberSource::SendEvent()");
  currentEvent_ = GetEventFactory().PopEvent();
  assert(currentEvent_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Physics"));
  SendAll(frame);
}

void I3UberSource::SendCalibration()
{
  log_debug("Entering I3UberSource::SendCalibration()");
  I3Time nextEvent = GetEventFactory().NextEventTime();
  currentCalibration_ = GetCalibrationFactory().GetCalibration(nextEvent);
  currentCalibrationRange_ 
    = GetCalibrationFactory().GetCalibrationValidityRange(nextEvent);
  assert(currentCalibration_);
  assert(currentCalibrationRange_.lower < currentCalibrationRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Calibration"));
  SendAll(frame);
}

void I3UberSource::SendGeometry()
{
  log_debug("Entering I3UberSource::SendGeometry()");
  I3Time nextEvent = GetEventFactory().NextEventTime();
  currentGeometry_ = GetGeometryFactory().GetGeometry(nextEvent);
  currentGeometryRange_ = 
    GetGeometryFactory().GetGeometryValidityRange(nextEvent);
  assert(currentGeometry_);
  assert(currentGeometryRange_.lower < currentGeometryRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Geometry"));
  SendAll(frame);
}

void I3UberSource::SendAll(I3Frame& frame)
{
  log_debug("Entering I3UberSource::SendAll()");
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

I3UberSource::Stream I3UberSource::NextStream()
{
  if(!GetEventFactory().MoreEvents())
    return NONE;

  I3Time eventTime = GetEventFactory().NextEventTime();
  if(!IsGeometryCurrent(eventTime))
    return GEOMETRY;
  if(!IsCalibrationCurrent(eventTime))
    return CALIBRATION;
  return EVENT;
}

bool I3UberSource::IsGeometryCurrent(I3Time time)
{
  if(!currentGeometry_)
    {
      log_debug("Geometry isn't current 'cause it hasn't been issued yet")
      return false;
    }
  if(currentGeometryRange_.lower < time && time < currentGeometryRange_.upper)
    {
      log_debug("Geometry is current, no worries");
      return true;
    }
  log_debug("Geometry needs updating.");
  return false;
}

bool I3UberSource::IsCalibrationCurrent(I3Time time)
{
  if(!currentCalibration_)
    {
      log_debug("Calibration isn't current 'cause it hasn't been issued yet");
      return false;
    }
  if(currentCalibrationRange_.lower < time &&
     time < currentCalibrationRange_.upper)
    {
      log_debug("Calibration is current, no worries!");
      return true;
    }
  log_debug("Calibration needs updating");
  return false;
}
