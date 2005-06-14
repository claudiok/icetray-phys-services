#include "phys-source/I3DummyPhysicsSource.h"

I3DummyPhysicsSource::I3DummyPhysicsSource(I3Context& context) : 
  I3PhysicsSource(context)
{
  eventsReturned_ = 0;
  maxEvents_ = 10;
}

EventPair I3DummyPhysicsSource::NextEvent()
{
  EventPair toReturn;
  toReturn.header = I3EventHeaderPtr(new I3EventHeader());
  toReturn.header->SetEventID(eventsReturned_);
  toReturn.header->SetStartTime(I3Time(2005,0));
  toReturn.event = I3EventPtr(new I3Event());
  eventsReturned_++;
  return toReturn;
}

bool I3DummyPhysicsSource::MoreEvents()
{
  if(eventsReturned_ < maxEvents_)
    return true;
  return false;
}
