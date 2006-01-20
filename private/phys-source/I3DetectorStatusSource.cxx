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

#include "phys-services/source/I3DetectorStatusSource.h"
#include "icetray/services/I3Execution.h"
#include "dataclasses/I3Time.h"
#include "icetray/I3TrayHeaders.h"
#include "icetray/I3Stream.h"
#include "icetray/services/I3Boxes.h"

//I3_MODULE(I3DetectorStatusSource);

I3DetectorStatusSource::I3DetectorStatusSource(const I3Context& context) : 
  I3Module(context)
{
  if(!I3Stream::StreamExists("DetectorStatus"))
    I3Stream::AddStream("DetectorStatus","DetectorStatus stream");

  AddOutBox("OutBox");
}

void I3DetectorStatusSource::Process()
{
  I3Frame& drivingFrame = GetBoxes().PopFrame();

  I3Time& drivingFrameTime = drivingFrame.Get<I3Time>("DrivingTime");

  if(drivingFrame.Exists("Geometry") || 
     drivingFrame.Exists("GeometryHeader") ||
     drivingFrame.Exists("Calibration") ||
     drivingFrame.Exists("CalibrationHeader") )
    {
      log_fatal("Somebody put these modules in the wrong order.  The "
		"DetectorStatus Source needs to go before the Geometry and "
		"Calibration Sources.");
    }

  if(!IsDetectorStatusCurrent(drivingFrameTime))
    {
      SendDetectorStatus(drivingFrameTime);
    }

  drivingFrame.Put(currentDetectorStatus_.status,
		   "DetectorStatus");
  drivingFrame.Put(currentDetectorStatus_.header,
		   "DetectorStatusHeader");
  PushFrame(drivingFrame,"OutBox");
  
}

I3Boxes& I3DetectorStatusSource::GetBoxes()
{
  return 
    I3ContextAccess<I3Boxes>::GetService(GetContext(),I3Boxes::DefaultName());
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
  frame.Put(currentDetectorStatus_.status,
	    "DetectorStatus");
  frame.Put(currentDetectorStatus_.header,
	    "DetectorStatusHeader");
  
  shared_ptr<I3Time> drivingTime(new I3Time(nextEvent));

  frame.Put(drivingTime, "DrivingTime");
  
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


