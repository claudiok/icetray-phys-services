#include "phys-services/empty-streams/I3EmptyEventService.h"
#include <dataclasses/I3Time.h>
#include <icetray/I3Frame.h>

I3EmptyEventService::I3EmptyEventService(int nframes) : nframes_(nframes),
							currentCount_(0)
{
  if(nframes_ < 0)
    log_fatal("Can't have fewer than 0 frames.");
}

bool I3EmptyEventService::MoreEvents()
{
  if(currentCount_ <= nframes_)
    return false;
  return true;
}

void I3EmptyEventService::PopEvent(I3Frame& frame)
{
  I3TimePtr time(new I3Time(2005,0));
  frame.Put("DrivingTime",time);
  currentCount_ +=1;
}
