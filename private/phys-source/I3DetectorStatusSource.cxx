/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3DetectorStatusSource.cxx 7067 2005-04-28 15:04:38Z pretz $
 *
 * @file I3DetectorStatusSource.cxx
 * @version $Revision:$
 * @date $Date: 2005-04-28 11:04:38 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */

#include "phys-source/I3DetectorStatusSource.h"
#include "services/I3Execution.h"
#include "dataclasses/I3Time.h"
#include "icetray/I3TrayHeaders.h"

I3DetectorStatusSource::I3DetectorStatusSource(I3Context& context) : 
  I3PhysicsModule(context)

{  
  log_trace(__PRETTY_FUNCTION__);
  AddOutBox("OutBox");

  if(!I3Stream::StreamExists("DetectorStatus"))
    I3Stream::AddStream("DetectorStatus","DetectorStatus Stream");
}

void I3DetectorStatusSource::Physics(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  I3Time eventTime = GetEventHeader(frame).GetStartTime();

  if(ShouldUpdateDetectorStatus(frame))
    {
      currentDetectorStatus_ = GetDetectorStatus(frame,eventTime);
      assert(currentDetectorStatus_);

      I3Frame& geoFrame = CreateFrame(I3Stream::FindStream("DetectorStatus"));
      CurrentDetectorStatusIntoFrame(geoFrame);

      PushFrame(geoFrame,"OutBox");
    }

  CurrentDetectorStatusIntoFrame(frame);

  PushFrame(frame,"OutBox");
}

void I3DetectorStatusSource::DetectorStatus(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  log_warn("Somebody upstream of I3DetectorStatusSource is putting "
	   "DetectorStatus frames into the system.  What's up with that");
  PushFrame(frame,"OutBox");
}

I3Frame& I3DetectorStatusSource::CreateFrame(const I3Stream& stop)
{
  log_trace(__PRETTY_FUNCTION__);
  I3Execution& execution = 
    I3ContextAccess<I3Execution>::GetService(GetContext(),
					     I3Execution::DefaultName());
  return execution.CreateFrame(stop);

}

bool I3DetectorStatusSource::ShouldUpdateDetectorStatus(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  if(!currentDetectorStatus_)
    return true;

  I3Time eventTime = GetEventHeader(frame).GetStartTime();
  
  if(currentDetectorStatus_.header->GetStartTime() < eventTime  &&
     currentDetectorStatus_.header->GetEndTime() > eventTime)
    {
      return false;
    }

  return true;
  
}

void I3DetectorStatusSource::CurrentDetectorStatusIntoFrame(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  I3FrameAccess<I3DetectorStatus>::Put(frame,
			      currentDetectorStatus_.status,
			      "DetectorStatus");
  I3FrameAccess<I3DetectorStatusHeader>::Put(frame,
				       currentDetectorStatus_.header,
				       "DetectorStatusHeader");
}
