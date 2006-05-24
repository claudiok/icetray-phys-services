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
#include <sstream>
#include "icetray/I3TrayHeaders.h"

#include <boost/preprocessor/stringize.hpp>
#define MUXER_ASSERT(condition) if(!(condition)) \
log_fatal("Muxer logic error %s",BOOST_PP_STRINGIZE(condition));

I3_MODULE(I3Muxer);

I3Muxer::I3Muxer(const I3Context& context) : I3Module(context),
					     currentEvent_(I3Frame::None),
					     currentEventQueued_(false),
                                             geoServiceName_("I3GeometryService")
{
  AddParameter("GeometryService",
               "Name of the geometry service to use",
               geoServiceName_);

  AddOutBox("OutBox");
}

void I3Muxer::Configure()
{
  GetParameter("GeometryService",geoServiceName_);
}


void I3Muxer::Process()
{
  log_debug("Entering I3Muxer::Process()");

  //
  // first check for 'meta streams', like TrayInfo, send em if they
  // exist.  These run at "speeds" unrelated to G/C/S/P
  //
  if (context_.Has<I3MetaService>())
    {
      I3FramePtr frame = context_.Get<I3MetaService>().PopMeta();
      if (frame)
	{
	  PushFrame(frame, "OutBox");
	  return;
	}
    }
    
  I3Frame::Stream next = NextStream();
  if (next == I3Frame::Physics)
    {
      SendEvent();
      return;
    }
  else if (next == I3Frame::Geometry)
    {
      SendGeometry();
      return;
    }
  else if (next == I3Frame::Calibration)
    {
      SendCalibration();
      return;
    }
  else if (next == I3Frame::DetectorStatus)
    {
      SendDetectorStatus();
      return;
    }
  else
    {
      RequestSuspension();
      return;
    }
  log_fatal("Something weird happened");
}

I3Frame::Stream 
I3Muxer::NextStream()
{
  if(!currentEventQueued_ && !context_.Get<I3EventService>().MoreEvents())
    return I3Frame::None;

  I3Time eventTime = NextEventTime();
  if(!IsGeometryCurrent(eventTime))
    return I3Frame::Geometry;
  if(!IsCalibrationCurrent(eventTime))
    return I3Frame::Calibration;
  if(!IsDetectorStatusCurrent(eventTime))
    return I3Frame::DetectorStatus;

  return I3Frame::Physics;
}


void I3Muxer::SendEvent()
{
  log_debug("Entering I3Muxer::SendEvent()");
  QueueUpEvent();

  I3FramePtr frame(new I3Frame(I3Frame::Physics));

  MUXER_ASSERT(currentEventQueued_);
  for(I3Frame::const_iterator iter = currentEvent_.begin (); 
      iter != currentEvent_.end() ; 
      iter++)
    {
      frame->Put(iter->first, iter->second);
    }
  MUXER_ASSERT(currentGeometry_);
  frame->Put(currentGeometry_);
  MUXER_ASSERT(currentCalibration_);
  frame->Put(currentCalibration_);
  MUXER_ASSERT(currentDetectorStatus_);
  frame->Put(currentDetectorStatus_);

  currentEventQueued_ = false;
  currentEvent_.clear();

  PushFrame(frame,"OutBox");
}

void I3Muxer::SendCalibration()
{
  log_debug("Entering I3Muxer::SendCalibration()");
  I3Time nextEvent = NextEventTime();
  currentCalibration_ = 
    context_.Get<I3CalibrationService>().GetCalibration(nextEvent);
  if(!currentCalibration_)
    log_fatal("got null calibration from the calibration service");
  currentCalibrationRange_ 
    = I3TimeRange(currentCalibration_->startTime,
		  currentCalibration_->endTime);
  if(currentCalibrationRange_.lower >= currentCalibrationRange_.upper)
    {
      log_fatal("Calibration range is not well-ordered.  lower:%s upper:%s",
		toString(currentCalibrationRange_.lower).c_str(),
		toString(currentCalibrationRange_.upper).c_str());
    }
  if(nextEvent < currentCalibrationRange_.lower ||
     nextEvent > currentCalibrationRange_.upper)
    {
      log_fatal("calibration range doesn't straddle the next event time "
		"lower:%s  upper:%s  eventTime:%s",
		toString(currentCalibrationRange_.lower).c_str(),
		toString(currentCalibrationRange_.upper).c_str(),
		toString(nextEvent).c_str());
    }
  I3FramePtr frame(new I3Frame(I3Frame::Calibration));

  MUXER_ASSERT(currentGeometry_);
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
  if(!currentDetectorStatus_)
    log_fatal("got null status from the status service");
  currentDetectorStatusRange_ 
    = I3TimeRange(currentDetectorStatus_->startTime,
		  currentDetectorStatus_->endTime);

  if(currentDetectorStatusRange_.lower >=
     currentDetectorStatusRange_.upper)
    {
      log_fatal("Status range is not well-ordered.  lower:%s upper:%s",
		toString(currentDetectorStatusRange_.lower).c_str(),
		toString(currentDetectorStatusRange_.upper).c_str());
    }
  if(nextEvent < currentDetectorStatusRange_.lower ||
     nextEvent > currentDetectorStatusRange_.upper)
    {
      log_fatal("status range doesn't straddle the next event time "
		"lower:%s  upper:%s  eventTime:%s",
		toString(currentDetectorStatusRange_.lower).c_str(),
		toString(currentDetectorStatusRange_.upper).c_str(),
		toString(nextEvent).c_str());
    }
  I3FramePtr frame(new I3Frame(I3Frame::DetectorStatus));

  MUXER_ASSERT(currentGeometry_);
  frame->Put(currentGeometry_);
  MUXER_ASSERT(currentCalibration_);
  frame->Put(currentCalibration_);
  frame->Put(currentDetectorStatus_);

  PushFrame(frame,"OutBox");
}

void I3Muxer::SendGeometry()
{
  log_debug("Entering I3Muxer::SendGeometry()");
  I3Time nextEvent = NextEventTime();
  currentGeometry_ = context_.Get<I3GeometryService>(geoServiceName_).GetGeometry(nextEvent);
  if(!currentGeometry_)
    log_fatal("got null geometry from the geometry service");
  currentGeometryRange_ = 
    I3TimeRange(currentGeometry_->startTime,
		currentGeometry_->endTime);
  if(currentGeometryRange_.lower >= currentGeometryRange_.upper)
    {
      log_fatal("Geometry range is not well-ordered. lower:%s upper:%s",
		toString(currentGeometryRange_.lower).c_str(),
		toString(currentGeometryRange_.upper).c_str());
    }
  if(nextEvent < currentGeometryRange_.lower ||
     nextEvent > currentGeometryRange_.upper)
    {
      log_fatal("geometry range doesn't straddle the next event time "
		"lower:%s  upper:%s  eventTime:%s",
		toString(currentGeometryRange_.lower).c_str(),
		toString(currentGeometryRange_.upper).c_str(),
		toString(nextEvent).c_str());
    }
  I3FramePtr frame(new I3Frame(I3Frame::Geometry));
  frame->Put(currentGeometry_);
  PushFrame(frame,"OutBox");
}

bool I3Muxer::IsGeometryCurrent(I3Time time)
{
  if(!currentGeometry_)
    {
      log_debug("Geometry isn't current 'cause it hasn't been issued yet");
      return false;
    }
  if(currentGeometryRange_.lower <= time && 
     time <= currentGeometryRange_.upper)
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
  if(currentCalibrationRange_.lower <= time &&
     time <= currentCalibrationRange_.upper)
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
  if(currentDetectorStatusRange_.lower <= time &&
     time <= currentDetectorStatusRange_.upper)
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
      MUXER_ASSERT(context_.Get<I3EventService>().MoreEvents());
      I3TimePtr eventTimePtr;
      I3Time eventTime = 
	context_.Get<I3EventService>().PopEvent(currentEvent_);
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

string I3Muxer::toString(I3Time& time)
{
  ostringstream out;
  out<<"{"<<time.GetUTCYear()<<","<<time.GetUTCDaqTime()<<"}";
  return out.str();
}
