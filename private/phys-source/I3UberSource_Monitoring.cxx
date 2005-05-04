/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3UberSource_Monitoring.cxx 7067 2005-04-28 15:04:38Z pretz $
 *
 * @file I3UberSource_Monitoring.cxx
 * @version $Revision:$
 * @date $Date: 2005-04-28 11:04:38 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */

#include "phys-source/I3UberSource_Monitoring.h"
#include <map>
#include "icetray/I3TrayHeaders.h"

I3UberSource_Monitoring::I3UberSource_Monitoring(I3Context& context) : I3Source(context)
{
  AddOutBox("OutBox");
  NoActiveInBox();
  if(!I3Stream::StreamExists("Physics"))
    I3Stream::AddStream("Physics","Physics event Stream");
  if(!I3Stream::StreamExists("Monitor"))
    I3Stream::AddStream("Monitor","Monitoring Stream");
  if(!I3Stream::StreamExists("Geometry"))
    I3Stream::AddStream("Geometry","Geometry Stream");
  if(!I3Stream::StreamExists("Calibration"))
    I3Stream::AddStream("Calibration","Calibration Stream");
  if(!I3Stream::StreamExists("DetectorStatus"))
    I3Stream::AddStream("DetectorStatus","DetectorStatus Stream");
}

void I3UberSource_Monitoring::Process()
{
  log_debug("Entering I3UberSource_Monitoring::Process()");
  Stream next = NextStream();
  switch (next)
      {
      case EVENT:
	SendMonitoring();
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

I3MonitoringOrigin& I3UberSource_Monitoring::GetMonitoringOrigin()
{
  return 
    I3ContextAccess<I3MonitoringOrigin>::GetService(GetContext(),
						I3MonitoringOrigin::DefaultName());
}

I3GeometryOrigin& I3UberSource_Monitoring::GetGeometryOrigin()
{
  return I3ContextAccess<I3GeometryOrigin>::
    GetService(GetContext(),
	       I3GeometryOrigin::DefaultName());
}

I3CalibrationOrigin& I3UberSource_Monitoring::GetCalibrationOrigin()
{
  return I3ContextAccess<I3CalibrationOrigin>::
    GetService(GetContext(),
	       I3CalibrationOrigin::DefaultName());
}

I3DetectorStatusOrigin& I3UberSource_Monitoring::GetDetectorStatusOrigin()
{
  return I3ContextAccess<I3DetectorStatusOrigin>::
    GetService(GetContext(),
	       I3DetectorStatusOrigin::DefaultName());
}

void I3UberSource_Monitoring::SendMonitoring()
{
  log_debug("Entering I3UberSource_Monitoring::SendMonitoring()");
  QueueUpMonitoring();
  assert(currentMonitoring_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Monitor"));
  SendAll(frame);
  currentMonitoring_.header = I3MonitoringHeaderPtr();
  currentMonitoring_.monitoring = I3MonitoringPtr();
}

void I3UberSource_Monitoring::SendCalibration()
{
  log_debug("Entering I3UberSource_Monitoring::SendCalibration()");
  I3Time nextMonitoring = NextMonitoringTime();
  currentCalibration_ = GetCalibrationOrigin().GetCalibration(nextMonitoring);
  currentCalibrationRange_ 
    = I3TimeRange(currentCalibration_.header->GetStartTime(),
		  currentCalibration_.header->GetEndTime());
  assert(currentCalibration_);
  assert(currentCalibrationRange_.lower < currentCalibrationRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Calibration"));
  SendAll(frame);
}

void I3UberSource_Monitoring::SendDetectorStatus()
{
  log_debug("Entering I3UberSource_Monitoring::SendDetectorStatus()");
  I3Time nextMonitoring = NextMonitoringTime();
  currentDetectorStatus_ = 
    GetDetectorStatusOrigin().GetDetectorStatus(nextMonitoring);
  currentDetectorStatusRange_ 
    = I3TimeRange(currentDetectorStatus_.header->GetStartTime(),
		  currentDetectorStatus_.header->GetEndTime());
  assert(currentDetectorStatus_);
  assert(currentDetectorStatusRange_.lower < 
	 currentDetectorStatusRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("DetectorStatus"));
  SendAll(frame);
}

void I3UberSource_Monitoring::SendGeometry()
{
  log_debug("Entering I3UberSource_Monitoring::SendGeometry()");
  I3Time nextMonitoring = NextMonitoringTime();
  currentGeometry_ = GetGeometryOrigin().GetGeometry(nextMonitoring);
  currentGeometryRange_ = 
    I3TimeRange(currentGeometry_.header->GetStartTime(),
		currentGeometry_.header->GetEndTime());
  assert(currentGeometry_);
  assert(currentGeometryRange_.lower < currentGeometryRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Geometry"));
  SendAll(frame);
}

void I3UberSource_Monitoring::SendAll(I3Frame& frame)
{
  log_debug("Entering I3UberSource_Monitoring::SendAll()");
  if(currentMonitoring_)
    {
      I3FrameAccess<I3Monitoring>::Put(frame,
				  currentMonitoring_.monitoring,
				  "Monitor");
      I3FrameAccess<I3MonitoringHeader>::Put(frame,
					currentMonitoring_.header,
					"MonitorHeader");
    }
  if(currentGeometry_)
    {
      I3FrameAccess<I3Geometry>::Put(frame,
				     currentGeometry_.geometry,
				     "Geometry");
      I3FrameAccess<I3GeometryHeader>::Put(frame,
					   currentGeometry_.header,
					   "GeometryHeader");
    }
  if(currentCalibration_)
    {
      I3FrameAccess<I3Calibration>::Put(frame,
				     currentCalibration_.calibration,
				     "Calibration");
      I3FrameAccess<I3CalibrationHeader>::Put(frame,
					   currentCalibration_.header,
					   "CalibrationHeader");
    }
  if(currentDetectorStatus_)
    {
      I3FrameAccess<I3DetectorStatus>::Put(frame,
				     currentDetectorStatus_.status,
				     "DetectorStatus");
      I3FrameAccess<I3DetectorStatusHeader>::Put(frame,
					   currentDetectorStatus_.header,
					   "DetectorStatusHeader");
    }

  PushFrame(frame,"OutBox");
}

I3UberSource_Monitoring::Stream I3UberSource_Monitoring::NextStream()
{
  if(!GetMonitoringOrigin().MoreMonitorings())
    return NONE;

  I3Time eventTime = NextMonitoringTime();
  if(!IsGeometryCurrent(eventTime))
    return GEOMETRY;
  if(!IsCalibrationCurrent(eventTime))
    return CALIBRATION;
  if(!IsDetectorStatusCurrent(eventTime))
    return DETECTORSTATUS;
  return EVENT;
}

bool I3UberSource_Monitoring::IsGeometryCurrent(I3Time time)
{
  if(!currentGeometry_)
    {
      log_debug("Geometry isn't current 'cause it hasn't been issued yet")
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

bool I3UberSource_Monitoring::IsCalibrationCurrent(I3Time time)
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

bool I3UberSource_Monitoring::IsDetectorStatusCurrent(I3Time time)
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

void I3UberSource_Monitoring::QueueUpMonitoring()
{
  if(!currentMonitoring_)
    {
      assert(GetMonitoringOrigin().MoreMonitorings());
      currentMonitoring_ = GetMonitoringOrigin().PopMonitoring();
    }
}

I3Time I3UberSource_Monitoring::NextMonitoringTime()
{
  QueueUpMonitoring();
  return currentMonitoring_.header->GetStartTime();
}
