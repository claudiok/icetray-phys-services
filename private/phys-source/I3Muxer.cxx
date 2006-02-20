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

#include <icetray/I3Context.h>
#include "phys-services/source/I3Muxer.h"
#include <map>
#include "icetray/I3TrayHeaders.h"

I3_MODULE(I3Muxer);

I3Muxer::I3Muxer(const I3Context& context) : I3Module(context),
					     currentEvent_(I3Frame::None),
					     currentEventQueued_(false)
{
  AddOutBox("OutBox");
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
	log_fatal("Something weird happened");
      }
}

void I3Muxer::SendEvent()
{
  log_debug("Entering I3Muxer::SendEvent()");
  QueueUpEvent();
  //  assert(currentEvent_);

  I3FramePtr frame(new I3Frame(I3Frame::Physics));

  assert(currentEventQueued_);
  for(I3Frame::const_iterator iter = currentEvent_.begin () ; 
      iter != currentEvent_.end() ; 
      iter++)
    {
      frame->Put(iter->first, iter->second);
    }
  assert(currentGeometry_);
  frame->Put(currentGeometry_);
  assert(currentCalibration_);
  frame->Put(currentCalibration_);
  assert(currentDetectorStatus_);
  frame->Put(currentDetectorStatus_);

  currentEventQueued_ = false;
  currentEvent_.clear();

  PushFrame(frame,"OutBox");
}

void I3Muxer::SendCalibration()
{
  log_debug("Entering I3Muxer::SendCalibration()");
  I3Time nextEvent = NextEventTime();
  currentCalibration_ = context_.Get<I3CalibrationService>().GetCalibration(nextEvent);
  currentCalibrationRange_ 
    = I3TimeRange(currentCalibration_->startTime,
		  currentCalibration_->endTime);
  assert(currentCalibration_);
  assert(currentCalibrationRange_.lower < currentCalibrationRange_.upper);
  I3FramePtr frame(new I3Frame(I3Frame::Calibration));

  assert(currentGeometry_);
  frame->Put(currentGeometry_);
  frame->Put(currentCalibration_);

  PushFrame(frame,"OutBox");
}

void I3Muxer::SendDetectorStatus()
{
  log_debug("Entering I3Muxer::SendDetectorStatus()");
  I3Time nextEvent = NextEventTime();
  currentDetectorStatus_ = 
    context_.Get<I3DetectorStatusService>().GetDetectorStatus(nextEvent);
  currentDetectorStatusRange_ 
    = I3TimeRange(currentDetectorStatus_->GetStartTime(),
		  currentDetectorStatus_->GetEndTime());
  assert(currentDetectorStatus_);
  assert(currentDetectorStatusRange_.lower < 
	 currentDetectorStatusRange_.upper);
  I3FramePtr frame(new I3Frame(I3Frame::DetectorStatus));

  assert(currentGeometry_);
  frame->Put(currentGeometry_);
  assert(currentCalibration_);
  frame->Put(currentCalibration_);
  frame->Put(currentDetectorStatus_);

  PushFrame(frame,"OutBox");
}

void I3Muxer::SendGeometry()
{
  log_debug("Entering I3Muxer::SendGeometry()");
  I3Time nextEvent = NextEventTime();
  currentGeometry_ = context_.Get<I3GeometryService>().GetGeometry(nextEvent);
  currentGeometryRange_ = 
    I3TimeRange(currentGeometry_->startTime,
		currentGeometry_->endTime);
  assert(currentGeometry_);
  assert(currentGeometryRange_.lower < currentGeometryRange_.upper);
  I3FramePtr frame(new I3Frame(I3Frame::Geometry));
  frame->Put(currentGeometry_);
  PushFrame(frame,"OutBox");
}

I3Muxer::Stream I3Muxer::NextStream()
{
  if(!context_.Get<I3EventService>().MoreEvents())
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

bool 
I3Muxer::IsDetectorStatusCurrent(I3Time time)
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

void 
I3Muxer::QueueUpEvent()
{
  if(!currentEventQueued_)
    {
      assert(context_.Get<I3EventService>().MoreEvents());
      I3TimePtr eventTimePtr;
      I3Time eventTime = context_.Get<I3EventService>().PopEvent(currentEvent_);
      eventTimePtr = I3TimePtr(new I3Time(eventTime));
      currentEvent_.Put("DrivingTime",eventTimePtr);
      currentEventQueued_ = true;
    }
}

I3Time 
I3Muxer::NextEventTime()
{
  QueueUpEvent();
  log_trace("About to look for DrivingTime in frame");
  I3Time returned = currentEvent_.Get<I3Time>("DrivingTime");
  return returned;
}