#include "phys-source/I3DummyEventOrigin.h"

I3DummyEventOrigin::I3DummyEventOrigin()
{
  currentTime_.SetDaqTime(2005,0);
  maxTime_.SetDaqTime(2005,100000);
}

bool I3DummyEventOrigin::MoreEvents()
{
  if(currentTime_ < maxTime_)
    return true;
  return false;
}

EventPair I3DummyEventOrigin::PopEvent()
{
  EventPair e;
  e.event = I3EventPtr(new I3Event());
  e.header = I3EventHeaderPtr(new I3EventHeader());
  currentTime_.SetDaqTime(currentTime_.GetUTCYear(),
			  currentTime_.GetUTCDaqTime() + 10000);
  e.header->SetStartTime(currentTime_);
  e.header->SetEndTime(currentTime_);
  return e;
}

I3Time I3DummyEventOrigin::NextEventTime()
{
  return currentTime_;
}
