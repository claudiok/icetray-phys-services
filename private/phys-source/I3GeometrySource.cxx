#include "phys-source/I3GeometrySource.h"
#include "services/I3Execution.h"
#include "dataclasses/I3Time.h"

I3GeometrySource::I3GeometrySource(I3Context& context) : 
  I3PhysicsModule(context)
{
  AddOutBox("OutBox");
}

void I3GeometrySource::Physics(I3Frame& frame)
{
  I3Time eventTime = GetEventHeader(frame).GetStartTime();
  if(!IsGeometryCurrent(eventTime))
    currentGeometry_ = GetGeometryFactory().GetGeometry(eventTime);
  SendGeometry(eventTime);
  PushFrame(frame,"OutBox");
}

void I3GeometrySource::Calibration(I3Frame & frame)
{
  I3Time calibTime = GetCalibrationHeader(frame).GetStartTime();
  if(!IsGeometryCurrent(calibTime))
    currentGeometry_ = GetGeometryFactory().GetGeometry(calibTime);
  SendGeometry(calibTime);
  PushFrame(frame,"OutBox");
}

void I3GeometrySource::Geometry(I3Frame& frame)
{
  log_warn("Somebody upstream of I3GeometrySource is putting "
	   "Geometry frames into the system.  What's up with that");
  PushFrame(frame,"OutBox");
}

void I3GeometrySource::SendGeometry(I3Time nextEvent)
{
  log_debug("Entering I3UberSource::SendGeometry()");
  currentGeometry_ = GetGeometryFactory().GetGeometry(nextEvent);
  currentGeometryRange_ 
    = GetGeometryFactory().GetGeometryValidityRange(nextEvent);
  assert(currentGeometry_);
  assert(currentGeometryRange_.lower < currentGeometryRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Geometry"));
  I3FrameAccess<I3Geometry>::Put(frame,
				    currentGeometry_.geometry,
				    "Geometry");
  I3FrameAccess<I3GeometryHeader>::Put(frame,
					  currentGeometry_.header,
					  "GeometryHeader");
  PushFrame(frame,"OutBox");
}

I3Frame& I3GeometrySource::CreateFrame(const I3Stream& stop)
{
  I3Execution& execution = 
    I3ContextAccess<I3Execution>::GetService(GetContext(),
					     I3Execution::DefaultName());
  return execution.CreateFrame(stop);

}

bool I3GeometrySource::IsGeometryCurrent(I3Time time)
{
  if(!currentGeometry_)
    {
      log_debug("Geometry isn't current 'cause it hasn't been issued yet");
      return false;
    }
  if(currentGeometryRange_.lower < time &&
     time < currentGeometryRange_.upper)
    {
      log_debug("Geometry is current, no worries!");
      return true;
    }
  log_debug("Geometry needs updating");
  return false;
}

I3GeometryOrigin& I3GeometrySource::GetGeometryFactory()
{
  return I3ContextAccess<I3GeometryOrigin>::
    GetService(GetContext(),
	       I3GeometryOrigin::DefaultName());
}
