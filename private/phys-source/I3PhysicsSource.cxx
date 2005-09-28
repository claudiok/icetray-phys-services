/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file 
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */


#include "phys-source/I3PhysicsSource.h"
#include "icetray/I3Context.h"
#include "icetray/I3TrayHeaders.h"

//I3_MODULE(I3PhysicsSource);

I3PhysicsSource::I3PhysicsSource(const I3Context& context) : I3Source(context)
{
  AddOutBox("OutBox");
  NoActiveInBox();
  if(!I3Stream::StreamExists("Physics"))
    I3Stream::AddStream("Physics","Event Stream");



}

void I3PhysicsSource::Process()
{
    log_trace("Entering I3PhysicsSource::Process()");
    if(MoreEvents())
      SendEvent();
    else
      RequestSuspension();
}

void I3PhysicsSource::SendEvent()
{
  log_trace("Entering I3PhysicsSource::SendEvent()");
  currentEvent_ = NextEvent();
  assert(currentEvent_);
  I3Frame& frame = CreateFrame(I3Stream::FindStream("Physics"));
  I3FrameAccess<I3Event>::Put(frame,
			      currentEvent_.event,
			      "Physics");
  I3FrameAccess<I3EventHeader>::Put(frame,
				    currentEvent_.header,
				    "PhysicsHeader");
 
  shared_ptr<I3Time> 
    eventTime(new I3Time(currentEvent_.header->GetStartTime()));;

  I3FrameAccess<I3Time>::Put(frame,eventTime,"DrivingTime");

  PushFrame(frame,"OutBox");
}

