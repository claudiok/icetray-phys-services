#include "phys-services/empty-streams/I3EmptyEventService.h"
#include <dataclasses/I3Time.h>
#include <icetray/I3Frame.h>

I3EmptyEventService::I3EmptyEventService(int nframes, I3Time eventTime) : 
  nframes_(nframes),currentCount_(0),eventTime_(eventTime)
{
  if(nframes_ < 0)
    {
      log_info("Configured for infinite events");
      nframes_ = -1;
    }
}

I3EmptyEventService::~I3EmptyEventService()
{
}

bool I3EmptyEventService::MoreEvents()
{
  if(nframes_ == -1)
    return true;
   
  if(currentCount_ >= nframes_)
    return false;
  return true;
}

I3Time I3EmptyEventService::PopEvent(I3Frame& frame)
{
  currentCount_ +=1;
  return eventTime_;
}
