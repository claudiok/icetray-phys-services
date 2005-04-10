#include "phys-source/I3DummyEventOrigin.h"

I3DummyEventOrigin::I3DummyEventOrigin(int eventsToReturn)
{
  maxEvents_ = eventsToReturn;
  currentEvent_ = 0;
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
  e.event = I3EventPtr(new I3Event());
  e.header = I3EventHeaderPtr(new I3EventHeader());

  I3Time eventTime;

  eventTime.SetDaqTime(2005,
		       0);

  e.header->SetStartTime(eventTime);
  e.header->SetEndTime(eventTime);

  currentEvent_++;

  return e;
}

