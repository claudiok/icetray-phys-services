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

#include "phys-source/I3CalibrationSource.h"
#include "services/I3Execution.h"
#include "dataclasses/I3Time.h"
#include "icetray/I3TrayHeaders.h"

I3CalibrationSource::I3CalibrationSource(I3Context& context) : 
  I3PhysicsModule(context)
{
  if(!I3Stream::StreamExists("Calibration"))
    I3Stream::AddStream("Calibration","Calibration Stream");

  AddOutBox("OutBox");
}

void I3CalibrationSource::Physics(I3Frame& frame)
{
  I3FrameAccess<I3Calibration>::Put(frame,
				    currentCalibration_.calibration,
				    "Calibration");
  I3FrameAccess<I3CalibrationHeader>::Put(frame,
					  currentCalibration_.header,
					  "CalibrationHeader");
  PushFrame(frame,"OutBox");
}

void I3CalibrationSource::DetectorStatus(I3Frame& frame)
{
  log_debug("Entering I3CalibrationSource::DetectorStatus");
  I3Time statusTime = GetDetectorStatusHeader(frame).GetStartTime();
  if(!IsCalibrationCurrent(statusTime))
    {
      SendCalibration(statusTime);
    }
  I3FrameAccess<I3Calibration>::Put(frame,
				    currentCalibration_.calibration,
				    "Calibration");
  I3FrameAccess<I3CalibrationHeader>::Put(frame,
					  currentCalibration_.header,
					  "CalibrationHeader");
  PushFrame(frame,"OutBox");
}


void I3CalibrationSource::Calibration(I3Frame& frame)
{
  log_debug("Entering I3CalibrationSource::Calibration()");
  log_warn("Somebody upstream of I3CalibrationSource is putting "
	   "Calibration frames into the system.  What's up with that");
  PushFrame(frame,"OutBox");
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
  I3FrameAccess<I3Calibration>::Put(frame,
				    currentCalibration_.calibration,
				    "Calibration");
  I3FrameAccess<I3CalibrationHeader>::Put(frame,
					  currentCalibration_.header,
					  "CalibrationHeader");
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


