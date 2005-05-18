/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3DummyEventOrigin.cxx
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#include "phys-source/I3DummyEventOrigin.h"
#include "dataclasses/I3MCEvent.h"
#include "dataclasses/I3MCEventHeader.h"

I3DummyEventOrigin::I3DummyEventOrigin(int eventsToReturn)
{
  maxEvents_ = eventsToReturn;
  currentEvent_ = 0;
  mcEvents_ = false;
}

void I3DummyEventOrigin::GiveNonMCEvents()
{
  mcEvents_ = false;
}

void I3DummyEventOrigin::GiveMCEvents()
{
  mcEvents_ = true;
}

bool I3DummyEventOrigin::MoreEvents()
{
  log_debug("current event %d of %d to send",currentEvent_,maxEvents_);
  if(currentEvent_ >= maxEvents_)
    return false;
  return true;
}

EventPair I3DummyEventOrigin::PopEvent()
{
  EventPair e;
  if(mcEvents_)
    {
      e.event = I3EventPtr(new I3MCEvent());
      e.header = I3EventHeaderPtr(new I3MCEventHeader());
    }
  else
    {
      e.event = I3EventPtr(new I3Event());
      e.header = I3EventHeaderPtr(new I3EventHeader());
    }

  I3Time eventTime;

  eventTime.SetDaqTime(2005,
		       0);

  e.header->SetStartTime(eventTime);
  e.header->SetEndTime(eventTime);

  currentEvent_++;

  return e;
}

