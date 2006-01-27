/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3CalibrationSource.cxx
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#include "phys-services/source/I3CalibrationSource.h"
#include "icetray/services/I3Execution.h"
#include "dataclasses/I3Time.h"
#include "icetray/I3TrayHeaders.h"
#include "icetray/services/I3Boxes.h"
#include "icetray/I3Stream.h"


I3CalibrationSource::I3CalibrationSource(const I3Context& context) : 
  I3Module(context)
{
  if(!I3Stream::StreamExists("Calibration"))
    I3Stream::AddStream("Calibration","Calibration Stream");

  AddOutBox("OutBox");
}

void I3CalibrationSource::Process()
{
  I3Frame& drivingFrame = GetBoxes().PopFrame();

  I3Time& drivingFrameTime = drivingFrame.Get<I3Time>("DrivingTime");

  if(drivingFrame.Exists("Geometry") || 
     drivingFrame.Exists("GeometryHeader") )
    {
      log_fatal("Somebody put these modules in the wrong order.  The "
		"Calibration Source needs to go before the Geometry Source ");
    }

  if(!IsCalibrationCurrent(drivingFrameTime))
    {
      SendCalibration(drivingFrameTime);
    }

  drivingFrame.Put("Calibration", currentCalibration_.calibration);
  drivingFrame.Put("CalibrationHeader", currentCalibration_.header);
  PushFrame(drivingFrame,"OutBox");

}

I3Boxes& I3CalibrationSource::GetBoxes()
{
  return 
    I3ContextAccess<I3Boxes>::GetService(GetContext(),I3Boxes::DefaultName());
}

void I3CalibrationSource::SendCalibration(I3Time nextEvent)
{
  log_debug("Entering I3CalibrationSource::SendCalibration()");
  currentCalibration_ = GetCalibration(nextEvent);
  currentCalibrationRange_ 
    = I3TimeRange(currentCalibration_.header->GetStartTime(),
		  currentCalibration_.header->GetEndTime()); 
  assert(currentCalibration_);
  assert(currentCalibrationRange_.lower < currentCalibrationRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Calibration"));
  frame.Put("Calibration", currentCalibration_.calibration);

  frame.Put("CalibrationHeader", currentCalibration_.header);

  shared_ptr<I3Time> drivingTime(new I3Time(nextEvent));
  
  frame.Put("DrivingTime", drivingTime);
  
  PushFrame(frame,"OutBox");
}

I3Frame& I3CalibrationSource::CreateFrame(const I3Stream& stop)
{
  I3Execution& execution = 
    I3ContextAccess<I3Execution>::GetService(GetContext(),
					     I3Execution::DefaultName());
  return execution.CreateFrame(stop);

}

bool I3CalibrationSource::IsCalibrationCurrent(I3Time time)
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


