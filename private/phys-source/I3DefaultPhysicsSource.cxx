#include "phys-source/I3DefaultPhysicsSource.h"
#include "dataclasses/I3MCEvent.h"
#include "dataclasses/I3MCEventHeader.h"

I3DefaultPhysicsSource::I3DefaultPhysicsSource(I3Context& context) : 
  I3PhysicsSource(context)
{
  eventsReturned_ = 0;
  maxEvents_ = 10;

  AddParameter("GiveMCEvents","Whether or not to return MC events",mcEvents_);
  AddParameter("EventsToReturn","The numbers of events to return",maxEvents_);
}

void I3DefaultPhysicsSource::Configure()
{
  GetParameter("GiveMCEvents",mcEvents_);
  GetParameter("EventsToReturn",maxEvents_);
}

EventPair I3DefaultPhysicsSource::NextEvent()
{
  EventPair toReturn;
  if(mcEvents_)
    {
      toReturn.header = I3EventHeaderPtr(new I3MCEventHeader());
      toReturn.event = I3EventPtr(new I3MCEvent());
    }
  else
    {
      toReturn.header = I3EventHeaderPtr(new I3EventHeader());
      toReturn.event = I3EventPtr(new I3Event());
    }

  toReturn.header->SetEventID(eventsReturned_);
  toReturn.header->SetStartTime(I3Time(2005,0));
  eventsReturned_++;
  return toReturn;
}

bool I3DefaultPhysicsSource::MoreEvents()
{
  if(eventsReturned_ < maxEvents_)
    return true;
  return false;
}