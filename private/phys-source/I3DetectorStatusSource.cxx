/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3DetectorStatusSource.cxx
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#include "phys-source/I3DetectorStatusSource.h"
#include "services/I3Execution.h"
#include "dataclasses/I3Time.h"
#include "icetray/I3TrayHeaders.h"

I3DetectorStatusSource::I3DetectorStatusSource(I3Context& context) : 
  I3PhysicsModule(context)
{
  if(!I3Stream::StreamExists("DetectorStatus"))
    I3Stream::AddStream("DetectorStatus","DetectorStatus stream");

  AddOutBox("OutBox");
}

void I3DetectorStatusSource::Physics(I3Frame& frame)
{
  log_debug("Entering I3DetectorStatusSource::Physics");
  I3Time eventTime = GetEventHeader(frame).GetStartTime();
  if(!IsDetectorStatusCurrent(eventTime))
    {
      SendDetectorStatus(eventTime);
    }
  I3FrameAccess<I3DetectorStatus>::Put(frame,
				    currentDetectorStatus_.status,
				    "DetectorStatus");
  I3FrameAccess<I3DetectorStatusHeader>::Put(frame,
					  currentDetectorStatus_.header,
					  "DetectorStatusHeader");
  PushFrame(frame,"OutBox");
}

void I3DetectorStatusSource::DetectorStatus(I3Frame& frame)
{
  log_debug("Entering I3DetectorStatusSource::DetectorStatus()");
  log_warn("Somebody upstream of I3DetectorStatusSource is putting "
	   "DetectorStatus frames into the system.  What's up with that");
  PushFrame(frame,"OutBox");
}

void I3DetectorStatusSource::SendDetectorStatus(I3Time nextEvent)
{
  log_debug("Entering I3DetectorStatusSource::SendDetectorStatus()");
  currentDetectorStatus_ = GetDetectorStatus(nextEvent);
  currentDetectorStatusRange_ 
    = I3TimeRange(currentDetectorStatus_.header->GetStartTime(),
		  currentDetectorStatus_.header->GetEndTime()); 
  assert(currentDetectorStatus_);
  assert(currentDetectorStatusRange_.lower < currentDetectorStatusRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("DetectorStatus"));
  I3FrameAccess<I3DetectorStatus>::Put(frame,
				    currentDetectorStatus_.status,
				    "DetectorStatus");
  I3FrameAccess<I3DetectorStatusHeader>::Put(frame,
					  currentDetectorStatus_.header,
					  "DetectorStatusHeader");
  PushFrame(frame,"OutBox");
}

I3Frame& I3DetectorStatusSource::CreateFrame(const I3Stream& stop)
{
  I3Execution& execution = 
    I3ContextAccess<I3Execution>::GetService(GetContext(),
					     I3Execution::DefaultName());
  return execution.CreateFrame(stop);

}

bool I3DetectorStatusSource::IsDetectorStatusCurrent(I3Time time)
{
  if(!currentDetectorStatus_)
    {
      log_debug("DetectorStatus isn't current 'cause it hasn't been issued yet");
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


