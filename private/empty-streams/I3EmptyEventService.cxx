#include "phys-services/empty-streams/I3EmptyEventService.h"
#include <dataclasses/I3Time.h>
#include <icetray/I3Frame.h>

I3EmptyEventService::I3EmptyEventService(int nframes) : nframes_(nframes),
							currentCount_(0)
{
  if(nframes_ < 0)
    log_fatal("Can't have fewer than 0 frames.");
}

I3EmptyEventService::~I3EmptyEventService()
{
}

bool I3EmptyEventService::MoreEvents()
{
  if(currentCount_ >= nframes_)
    return false;
  return true;
}

I3Time I3EmptyEventService::PopEvent(I3Frame& frame)
{
  currentCount_ +=1;
  return I3Time(2006,0);
}
