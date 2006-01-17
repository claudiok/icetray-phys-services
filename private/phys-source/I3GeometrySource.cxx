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

#include "phys-services/source/I3GeometrySource.h"
#include "icetray/services/I3Execution.h"
#include "dataclasses/I3Time.h"
#include "icetray/I3TrayHeaders.h"
#include "icetray/I3Stream.h"
#include "icetray/services/I3Boxes.h"

//I3_MODULE(I3GeometrySource);

I3GeometrySource::I3GeometrySource(const I3Context& context) : 
  I3Module(context)
{
  if(!I3Stream::StreamExists("Geometry"))
    I3Stream::AddStream("Geometry","Geometry Stream");

  AddOutBox("OutBox");
}

void I3GeometrySource::Process()
{
 I3Frame& drivingFrame = GetBoxes().PopFrame();

  I3Time& drivingFrameTime = 
    I3FrameAccess<I3Time>::Get(drivingFrame,"DrivingTime");

  if(!IsGeometryCurrent(drivingFrameTime))
    {
      SendGeometry(drivingFrameTime);
    }

  I3FrameAccess<I3Geometry>::Put(drivingFrame,
				 currentGeometry_.geometry,
				 "Geometry");
  I3FrameAccess<I3GeometryHeader>::Put(drivingFrame,
				       currentGeometry_.header,
				       "GeometryHeader");
  PushFrame(drivingFrame,"OutBox");
}

I3Boxes& I3GeometrySource::GetBoxes()
{
  return 
    I3ContextAccess<I3Boxes>::GetService(GetContext(),I3Boxes::DefaultName());
}


void I3GeometrySource::SendGeometry(I3Time nextEvent)
{
  log_debug("Entering IGeometrySource::SendGeometry()");
  currentGeometry_ = GetGeometry(nextEvent);
  currentGeometryRange_ = I3TimeRange(currentGeometry_.header->GetStartTime(),
				      currentGeometry_.header->GetEndTime());
  assert(currentGeometry_);
  assert(currentGeometryRange_.lower < currentGeometryRange_.upper);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Geometry"));
  I3FrameAccess<I3Geometry>::Put(frame,
				 currentGeometry_.geometry,
				 "Geometry");
  I3FrameAccess<I3GeometryHeader>::Put(frame,
				       currentGeometry_.header,
				       "GeometryHeader");

  shared_ptr<I3Time> drivingTime(new I3Time(nextEvent));
  
  I3FrameAccess<I3Time>::Put(frame,
			     drivingTime,
			     "DrivingTime");
  
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


