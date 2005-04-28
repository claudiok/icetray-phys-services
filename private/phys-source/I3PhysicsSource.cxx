/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file 
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */


#include "phys-source/I3PhysicsSource.h"
#include "icetray/I3Context.h"
#include "icetray/I3TrayHeaders.h"

I3PhysicsSource::I3PhysicsSource(I3Context& context) : I3Source(context)
{
  AddOutBox("OutBox");
  NoActiveInBox();
  if(!I3Stream::StreamExists("Physics"))
    I3Stream::AddStream("Physics","Event Stream");
  if(!I3Stream::StreamExists("Geometry"))
    I3Stream::AddStream("Geometry","Geometry Stream");
  if(!I3Stream::StreamExists("Calibration"))
    I3Stream::AddStream("Calibration","Calibration Stream");
  if(!I3Stream::StreamExists("DetectorStatus"))
    I3Stream::AddStream("DetectorStatus","DetectorStatus stream");
}

void I3PhysicsSource::Process()
{
    log_debug("Entering I3PhysicsSource::Process()");
    if(GetEventFactory().MoreEvents())
      SendEvent();
    else
      RequestSuspension();
}

void I3PhysicsSource::SendEvent()
{
  log_debug("Entering I3PhysicsSource::SendEvent()");
  currentEvent_ = GetEventFactory().PopEvent();
  assert(currentEvent_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Physics"));
  I3FrameAccess<I3Event>::Put(frame,
			      currentEvent_.event,
			      "Physics");
  I3FrameAccess<I3EventHeader>::Put(frame,
				    currentEvent_.header,
				    "PhysicsHeader");
  PushFrame(frame,"OutBox");
}

I3EventOrigin& I3PhysicsSource::GetEventFactory()
{
  return 
    I3ContextAccess<I3EventOrigin>::GetService(GetContext(),
					       I3EventOrigin::DefaultName());
}
