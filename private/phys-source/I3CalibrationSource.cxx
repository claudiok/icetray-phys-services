/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3DetectorStatusSource.cxx
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#include "phys-source/I3CalibrationSource.h"
#include "services/I3Execution.h"
#include "dataclasses/I3Time.h"
#include "icetray/I3TrayHeaders.h"

I3CalibrationSource::I3CalibrationSource(I3Context& context) : 
  I3PhysicsModule(context)
{
  log_trace(__PRETTY_FUNCTION__);
  AddOutBox("OutBox");

  if(!I3Stream::StreamExists("Calibration"))
    I3Stream::AddStream("Calibration","Calibration Stream");
}

void I3CalibrationSource::Physics(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  I3Time eventTime = GetEventHeader(frame).GetStartTime();

  if(ShouldUpdateCalibration(frame))
    {
      currentCalibration_ = GetCalibration(frame,eventTime);
      assert(currentCalibration_);

      I3Frame& geoFrame = CreateFrame(I3Stream::FindStream("Calibration"));
      CurrentCalibrationIntoFrame(geoFrame);

      PushFrame(geoFrame,"OutBox");
    }

  CurrentCalibrationIntoFrame(frame);

  PushFrame(frame,"OutBox");
}

void I3CalibrationSource::Calibration(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  log_warn("Somebody upstream of I3CalibrationSource is putting "
	   "Calibration frames into the system.  What's up with that");
  PushFrame(frame,"OutBox");
}

void I3CalibrationSource::DetectorStatus(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  if(currentCalibration_)
    CurrentCalibrationIntoFrame(frame);
  PushFrame(frame,"OutBox");
}

I3Frame& I3CalibrationSource::CreateFrame(const I3Stream& stop)
{
  log_trace(__PRETTY_FUNCTION__);
  I3Execution& execution = 
    I3ContextAccess<I3Execution>::GetService(GetContext(),
					     I3Execution::DefaultName());
  return execution.CreateFrame(stop);

}

bool I3CalibrationSource::ShouldUpdateCalibration(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  if(!currentCalibration_)
    return true;

  I3Time eventTime = GetEventHeader(frame).GetStartTime();
  
  if(currentCalibration_.header->GetStartTime() < eventTime  &&
     currentCalibration_.header->GetEndTime() > eventTime)
    {
      return false;
    }

  return true;
  
}

void I3CalibrationSource::CurrentCalibrationIntoFrame(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  I3FrameAccess<I3Calibration>::Put(frame,
			      currentCalibration_.calibration,
			      "Calibration");
  I3FrameAccess<I3CalibrationHeader>::Put(frame,
				       currentCalibration_.header,
				       "CalibrationHeader");
}
