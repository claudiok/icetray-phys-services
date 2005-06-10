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

#include "phys-source/I3GeometrySource.h"
#include "services/I3Execution.h"
#include "dataclasses/I3Time.h"
#include "icetray/I3TrayHeaders.h"

I3GeometrySource::I3GeometrySource(I3Context& context) : 
  I3PhysicsModule(context)
{
  log_trace(__PRETTY_FUNCTION__);
  AddOutBox("OutBox");

  if(!I3Stream::StreamExists("Geometry"))
    I3Stream::AddStream("Geometry","Geometry Stream");
}

void I3GeometrySource::Physics(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  I3Time eventTime = GetEventHeader(frame).GetStartTime();

  if(ShouldUpdateGeometry(frame))
    {
      currentGeometry_ = GetGeometry(frame,eventTime);
      assert(currentGeometry_);

      I3Frame& geoFrame = CreateFrame(I3Stream::FindStream("Geometry"));
      CurrentGeometryIntoFrame(geoFrame);

      PushFrame(geoFrame,"OutBox");
    }

  CurrentGeometryIntoFrame(frame);

  PushFrame(frame,"OutBox");
}

void I3GeometrySource::Geometry(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  log_warn("Somebody upstream of I3GeometrySource is putting "
	   "Geometry frames into the system.  What's up with that");
  PushFrame(frame,"OutBox");
}

void I3GeometrySource::Calibration(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  if(currentGeometry_)
    CurrentGeometryIntoFrame(frame);
  PushFrame(frame,"OutBox");
}

void I3GeometrySource::DetectorStatus(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  if(currentGeometry_)
    CurrentGeometryIntoFrame(frame);
  PushFrame(frame,"OutBox");
}

I3Frame& I3GeometrySource::CreateFrame(const I3Stream& stop)
{
  log_trace(__PRETTY_FUNCTION__);
  I3Execution& execution = 
    I3ContextAccess<I3Execution>::GetService(GetContext(),
					     I3Execution::DefaultName());
  return execution.CreateFrame(stop);

}

bool I3GeometrySource::ShouldUpdateGeometry(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  if(!currentGeometry_)
    return true;

  I3Time eventTime = GetEventHeader(frame).GetStartTime();
  
  if(currentGeometry_.header->GetStartTime() < eventTime  &&
     currentGeometry_.header->GetEndTime() > eventTime)
    {
      return false;
    }

  return true;
  
}

void I3GeometrySource::CurrentGeometryIntoFrame(I3Frame& frame)
{
  log_trace(__PRETTY_FUNCTION__);
  I3FrameAccess<I3Geometry>::Put(frame,
			      currentGeometry_.geometry,
			      "Geometry");
  I3FrameAccess<I3GeometryHeader>::Put(frame,
				       currentGeometry_.header,
				       "GeometryHeader");
}
