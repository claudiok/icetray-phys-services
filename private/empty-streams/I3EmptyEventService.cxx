#include "phys-services/empty-streams/I3EmptyEventService.h"
#include <dataclasses/I3Time.h>
#include <dataclasses/physics/I3EventHeader.h>
#include <icetray/I3Frame.h>

I3EmptyEventService::I3EmptyEventService(int nframes, I3Time eventTime, unsigned runNumber) : 
  nframes_(nframes),currentCount_(0),eventTime_(eventTime),runNumber_(runNumber)
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
  if(runNumber_ > 0) // Someone has specified a run number
    {
      //Lets make a frame header that can be used for testing
      I3EventHeaderPtr eventHeader_(new I3EventHeader);
      eventHeader_->SetStartTime(eventTime_);
      eventHeader_->SetRunID(runNumber_);
      eventHeader_->SetSubRunID(0);
      eventHeader_->SetEventID(currentCount_);
      //Lets put it in the frame
      frame.Put<I3EventHeader>(eventHeader_);
    }
  currentCount_ +=1;
  return eventTime_;
}
