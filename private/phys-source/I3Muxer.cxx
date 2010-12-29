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
#include <phys-services/source/I3Muxer.h>
I3_MODULE(I3Muxer);

#include <map>
#include <sstream>

#include <icetray/I3Context.h>
#include <icetray/I3TrayHeaders.h>
#include <dataclasses/calibration/I3Calibration.h>
#include <dataclasses/geometry/I3Geometry.h>
#include <dataclasses/status/I3DetectorStatus.h>

#include <boost/preprocessor/stringize.hpp>
#define MUXER_ASSERT(condition) if(!(condition)) \
log_fatal("muxer logic error %s",BOOST_PP_STRINGIZE(condition));


const char* I3Muxer::DRIVING_TIME = "DrivingTime";


I3Muxer::I3Muxer(const I3Context& context) : I3Module(context),
                 currentEvent_(I3Frame::Physics),
                 currentEventQueued_(false),
                 geometryServiceName_(I3DefaultName<I3GeometryService>::value()),
                 statusServiceName_(I3DefaultName<I3DetectorStatusService>::value()),
                 calibrationServiceName_(I3DefaultName<I3CalibrationService>::value()),
                 eventServiceName_(I3DefaultName<I3EventService>::value())
{
  AddParameter("GeometryService",
               "Name of the geometry service to use",
               geometryServiceName_);

  AddParameter("CalibrationService",
               "Name of the calibration service to use",
               calibrationServiceName_);

  AddParameter("DetectorStatusService",
               "Name of the detector status service to use",
               statusServiceName_);

  AddParameter("EventService",
               "Name of the event (or 'driving time') service to use",
               eventServiceName_);

  AddOutBox("OutBox");
}

void I3Muxer::Configure()
{
  GetParameter("GeometryService",geometryServiceName_);
  GetParameter("CalibrationService",calibrationServiceName_);
  GetParameter("DetectorStatusService",statusServiceName_);
  GetParameter("EventService",eventServiceName_);

  geometryService_ = context_.Get<I3GeometryServicePtr>(geometryServiceName_);
  calibrationService_ = context_.Get<I3CalibrationServicePtr>(calibrationServiceName_);
  statusService_ = context_.Get<I3DetectorStatusServicePtr>(statusServiceName_);
  eventService_ = context_.Get<I3EventServicePtr>(eventServiceName_);

  if (context_.Has<I3MetaServicePtr>())
    metaService_ = context_.Get<I3MetaServicePtr>();

  log_trace("Services: G %p C %p D %p E %p M %p", geometryService_.get(), calibrationService_.get(),
    statusService_.get(), eventService_.get(), metaService_.get());
}


I3FramePtr
I3Muxer::PopFrame()
{
  //
  // first check for 'meta streams', like TrayInfo, send em if they
  // exist.  These run at "speeds" unrelated to G/C/S/P
  //  
  if (metaService_)
    {
      I3FramePtr frame = metaService_->PopMeta();
      if (frame) return frame;
    }

  I3Frame::Stream next = NextStream();
  if (next == I3Frame::Physics)
    {
      return SendEvent();
    }
  else if (next == I3Frame::Geometry)
    {
      return SendGeometry();
    }
  else if (next == I3Frame::Calibration)
    {
      return SendCalibration();
    }
  else if (next == I3Frame::DetectorStatus)
    {
      return SendDetectorStatus();
    }
  else
    {
      return I3FramePtr();
    }
}

void I3Muxer::Process()
{
  log_debug("Entering I3Muxer::Process()");

  I3FramePtr frame = PopFrame();
  if (frame) {
    PushFrame(frame, "OutBox");
    return;
  } else {
    RequestSuspension();
    return;
  }

  log_fatal("Something weird happened");
}

I3Frame::Stream 
I3Muxer::NextStream()
{
  if(!currentEventQueued_ && !eventService_->MoreEvents())
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


I3FramePtr
I3Muxer::SendEvent()
{
  log_debug("Entering I3Muxer::SendEvent()");
  QueueUpEvent();

  I3FramePtr frame(new I3Frame(I3Frame::Physics));

  MUXER_ASSERT(currentEventQueued_);
  for(I3Frame::typename_iterator iter = currentEvent_.typename_begin (); 
      iter != currentEvent_.typename_end() ; 
      iter++)
    {
      frame->take(currentEvent_, iter->first);
    }
  MUXER_ASSERT(currentGeometry_);
  frame->Put("I3Geometry", currentGeometry_,  'G');
  MUXER_ASSERT(currentCalibration_);
  frame->Put("I3Calibration", currentCalibration_,  'C');
  MUXER_ASSERT(currentDetectorStatus_);
  frame->Put("I3DetectorStatus", currentDetectorStatus_,  'D');

  currentEventQueued_ = false;
  currentEvent_.clear();

  return frame;
}

I3FramePtr
I3Muxer::SendCalibration()
{
  log_debug("Entering I3Muxer::SendCalibration()");
  I3Time nextEvent = NextEventTime();
  currentCalibration_ = 
    calibrationService_->GetCalibration(nextEvent);
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
		"(event time is outside calibration range) "
                "lower:%s  upper:%s  eventTime:%s",
                toString(currentCalibrationRange_.lower).c_str(),
                toString(currentCalibrationRange_.upper).c_str(),
                toString(nextEvent).c_str());
    }
  I3FramePtr frame(new I3Frame(I3Frame::Calibration));

  MUXER_ASSERT(currentGeometry_);
  frame->Put("I3Geometry", currentGeometry_,  'G');
  frame->Put("I3Calibration", currentCalibration_,  'C');

  return frame;
}

I3FramePtr
I3Muxer::SendDetectorStatus()
{
  log_debug("Entering I3Muxer::SendDetectorStatus()");
  I3Time nextEvent = NextEventTime();
  currentDetectorStatus_ = 
    statusService_->GetDetectorStatus(nextEvent);
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
		"(event time is outside status range) "
                "lower:%s  upper:%s  eventTime:%s",
                toString(currentDetectorStatusRange_.lower).c_str(),
                toString(currentDetectorStatusRange_.upper).c_str(),
                toString(nextEvent).c_str());
    }
  I3FramePtr frame(new I3Frame(I3Frame::DetectorStatus));

  MUXER_ASSERT(currentGeometry_);
  frame->Put("I3Geometry", currentGeometry_,  'G');
  MUXER_ASSERT(currentCalibration_);
  frame->Put("I3Calibration", currentCalibration_,  'C');
  frame->Put("I3DetectorStatus", currentDetectorStatus_,  'D');

  return frame;
}

I3FramePtr
I3Muxer::SendGeometry()
{
  log_debug("Entering I3Muxer::SendGeometry()");
  I3Time nextEvent = NextEventTime();
  currentGeometry_ = geometryService_->GetGeometry(nextEvent);
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
  if(nextEvent < currentGeometryRange_.lower
     || nextEvent > currentGeometryRange_.upper)
    {
      log_fatal("geometry range doesn't straddle the next event time "
		"(event time is outside geometry range) "
                "lower:%s  upper:%s  eventTime:%s",
                toString(currentGeometryRange_.lower).c_str(),
                toString(currentGeometryRange_.upper).c_str(),
                toString(nextEvent).c_str());
    }
  I3FramePtr frame(new I3Frame(I3Frame::Geometry));
  frame->Put("I3Geometry", currentGeometry_,  'G');
  
  return frame;
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
      MUXER_ASSERT(eventService_->MoreEvents());
      I3TimePtr eventTimePtr;
      I3Time eventTime = 
      eventService_->PopEvent(currentEvent_);
      eventTimePtr = I3TimePtr(new I3Time(eventTime));
      currentEvent_.Put(DRIVING_TIME,eventTimePtr, 'P');
      currentEventQueued_ = true;
    }
}

I3Time 
I3Muxer::NextEventTime()
{
  QueueUpEvent();
  log_trace("About to look for DrivingTime in frame");
  I3Time returned = currentEvent_.Get<I3Time>(DRIVING_TIME);
  return returned;
}

string I3Muxer::toString(I3Time& time)
{
  ostringstream out;
  out<<"{"<<time.GetUTCYear()<<","<<time.GetUTCDaqTime()<<"}";
  return out.str();
}
