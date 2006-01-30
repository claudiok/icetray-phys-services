/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3Muxer.cxx
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#include "phys-services/source/I3Muxer.h"
#include <map>
#include "icetray/I3TrayHeaders.h"

#warning null reference
I3Muxer::I3Muxer(I3Context& context) : I3Source(context),
						 currentEvent_(*(I3Stream*)NULL),
						 currentEventQueued_(false)
{
  AddOutBox("OutBox");
  NoActiveInBox();
  if(!I3Stream::StreamExists("Physics"))
    I3Stream::AddStream("Physics","Event Stream");
  if(!I3Stream::StreamExists("Geometry"))
    I3Stream::AddStream("Geometry","Geometry Stream");
  if(!I3Stream::StreamExists("Calibration"))
    I3Stream::AddStream("Calibration","Calibration Stream");
  if(!I3Stream::StreamExists("DetectorStatus"))
    I3Stream::AddStream("DetectorStatus","DetectorStatus Stream");
}

void I3Muxer::Process()
{
  log_debug("Entering I3Muxer::Process()");
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
      case DETECTORSTATUS:
	SendDetectorStatus();
	return;
      case NONE:
	RequestSuspension();
	return;
      default:
	Fatal("Something weird happened");
      }
}

I3EventOrigin& I3Muxer::GetEventOrigin()
{
  return 
    I3ContextAccess<I3EventOrigin>::GetService(GetContext(),
						I3EventOrigin::DefaultName());
}

I3GeometryOrigin& I3Muxer::GetGeometryOrigin()
{
  return I3ContextAccess<I3GeometryOrigin>::
    GetService(GetContext(),
	       I3GeometryOrigin::DefaultName());
}

I3CalibrationOrigin& I3Muxer::GetCalibrationOrigin()
{
  return I3ContextAccess<I3CalibrationOrigin>::
    GetService(GetContext(),
	       I3CalibrationOrigin::DefaultName());
}

I3DetectorStatusOrigin& I3Muxer::GetDetectorStatusOrigin()
{
  return I3ContextAccess<I3DetectorStatusOrigin>::
    GetService(GetContext(),
	       I3DetectorStatusOrigin::DefaultName());
}

void I3Muxer::SendEvent()
{
  log_debug("Entering I3Muxer::SendEvent()");
  QueueUpEvent();
  //  assert(currentEvent_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Physics"));
  SendAll(frame);

  currentEventQueued_ = false;
  currentEvent_.clear();

}

void I3Muxer::SendCalibration()
{
  log_debug("Entering I3Muxer::SendCalibration()");
  I3Time nextEvent = NextEventTime();
  currentCalibration_ = GetCalibrationOrigin().GetCalibration(nextEvent);
  currentCalibrationRange_ 
    = I3TimeRange(currentCalibration_.header->GetStartTime(),
		  currentCalibration_.header->GetEndTime());
  assert(currentCalibration_);
  assert(currentCalibrationRange_.lower < currentCalibrationRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Calibration"));
  SendAll(frame);
}

void I3Muxer::SendDetectorStatus()
{
  log_debug("Entering I3Muxer::SendDetectorStatus()");
  I3Time nextEvent = NextEventTime();
  currentDetectorStatus_ = 
    GetDetectorStatusOrigin().GetDetectorStatus(nextEvent);
  currentDetectorStatusRange_ 
    = I3TimeRange(currentDetectorStatus_.header->GetStartTime(),
		  currentDetectorStatus_.header->GetEndTime());
  assert(currentDetectorStatus_);
  assert(currentDetectorStatusRange_.lower < 
	 currentDetectorStatusRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("DetectorStatus"));
  SendAll(frame);
}

void I3Muxer::SendGeometry()
{
  log_debug("Entering I3Muxer::SendGeometry()");
  I3Time nextEvent = NextEventTime();
  currentGeometry_ = GetGeometryOrigin().GetGeometry(nextEvent);
  currentGeometryRange_ = 
    I3TimeRange(currentGeometry_.header->GetStartTime(),
		currentGeometry_.header->GetEndTime());
  assert(currentGeometry_);
  assert(currentGeometryRange_.lower < currentGeometryRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Geometry"));
  SendAll(frame);
}

void I3Muxer::SendAll(I3Frame& frame)
{
  log_debug("Entering I3Muxer::SendAll()");
  if(currentEventQueued_)
    {
      for(I3Frame::iterator iter = currentEvent_.begin () ; 
	  iter != currentEvent_.end() ; 
	  iter++)
	{
	  frame[iter->first] = iter->second;
	}
    }
  if(currentGeometry_)
    {
      frame.Put("Geometry",currentGeometry_.geometry);
      frame.Put("GeometryHeader",currentGeometry_.header);
    }
  if(currentCalibration_)
    {
      frame.Put("Calibration",currentCalibration_.calibration);
      frame.Put("CalibrationHeader",currentCalibration_.header);
    }
  if(currentDetectorStatus_)
    {
      frame.Put("DetectorStatus",currentDetectorStatus_.status);
      frame.Put("DetectorStatusHeader",currentDetectorStatus_.header);
    }

  PushFrame(frame,"OutBox");
}

I3Muxer::Stream I3Muxer::NextStream()
{
  if(!GetEventOrigin().MoreEvents())
    return NONE;

  I3Time eventTime = NextEventTime();
  if(!IsGeometryCurrent(eventTime))
    return GEOMETRY;
  if(!IsCalibrationCurrent(eventTime))
    return CALIBRATION;
  if(!IsDetectorStatusCurrent(eventTime))
    return DETECTORSTATUS;
  return EVENT;
}

bool I3Muxer::IsGeometryCurrent(I3Time time)
{
  if(!currentGeometry_)
    {
      log_debug("Geometry isn't current 'cause it hasn't been issued yet");
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

bool I3Muxer::IsCalibrationCurrent(I3Time time)
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

bool I3Muxer::IsDetectorStatusCurrent(I3Time time)
{
  if(!currentDetectorStatus_)
    {
      log_debug("DetectorStatus isn't current 'cause it "
		"hasn't been issued yet");
      return false;
    }
  if(currentDetectorStatusRange_.lower < time &&
     time < currentDetectorStatusRange_.upper)
    {
      log_debug("DetectorStatus is current, no worries!");
      return true;
    }
  log_debug("DetectorStatus needs updating");
  return false;
}

void I3Muxer::QueueUpEvent()
{
  if(!currentEventQueued_)
    {
      assert(GetEventOrigin().MoreEvents());
      GetEventOrigin().PopEvent(currentEvent_);
      currentEventQueued_ = true;
    }
}

I3Time I3Muxer::NextEventTime()
{
  QueueUpEvent();
  I3Time returned = currentEvent_.Get<I3Time>("DrivingTime");
  return returned;
}
