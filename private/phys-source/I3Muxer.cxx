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

I3_MODULE(I3Muxer);

#warning null reference
I3Muxer::I3Muxer(const I3Context& context) : I3Source(context),
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

I3EventService& I3Muxer::GetEventService()
{
  return 
    I3ContextAccess<I3EventService>::GetService(GetContext(),
						I3EventService::DefaultName());
}

I3GeometryService& I3Muxer::GetGeometryService()
{
  return I3ContextAccess<I3GeometryService>::
    GetService(GetContext(),
	       I3GeometryService::DefaultName());
}

I3CalibrationService& I3Muxer::GetCalibrationService()
{
  return I3ContextAccess<I3CalibrationService>::
    GetService(GetContext(),
	       I3CalibrationService::DefaultName());
}

I3DetectorStatusService& I3Muxer::GetDetectorStatusService()
{
  return I3ContextAccess<I3DetectorStatusService>::
    GetService(GetContext(),
	       I3DetectorStatusService::DefaultName());
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
  currentCalibration_ = GetCalibrationService().GetCalibration(nextEvent);
  currentCalibrationRange_ 
    = I3TimeRange(currentCalibration_->GetStartTime(),
		  currentCalibration_->GetEndTime());
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
    GetDetectorStatusService().GetDetectorStatus(nextEvent);
  currentDetectorStatusRange_ 
    = I3TimeRange(currentDetectorStatus_->GetStartTime(),
		  currentDetectorStatus_->GetEndTime());
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
  currentGeometry_ = GetGeometryService().GetGeometry(nextEvent);
  currentGeometryRange_ = 
    I3TimeRange(currentGeometry_->GetStartTime(),
		currentGeometry_->GetEndTime());
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
      frame.Put("Geometry",currentGeometry_);
    }
  if(currentCalibration_)
    {
      frame.Put("Calibration",currentCalibration_);
    }
  if(currentDetectorStatus_)
    {
      frame.Put("DetectorStatus",currentDetectorStatus_);
    }

  PushFrame(frame,"OutBox");
}

I3Muxer::Stream I3Muxer::NextStream()
{
  if(!GetEventService().MoreEvents())
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
      assert(GetEventService().MoreEvents());
      I3TimePtr eventTimePtr;
      I3Time eventTime = GetEventService().PopEvent(currentEvent_);
      eventTimePtr = I3TimePtr(new I3Time(eventTime));
      currentEvent_.Put("DrivingTime",eventTimePtr);
      currentEventQueued_ = true;
    }
}

I3Time I3Muxer::NextEventTime()
{
  QueueUpEvent();
  I3Time returned = currentEvent_.Get<I3Time>("DrivingTime");
  return returned;
}
