#include <sstream>
#include "phys-services/I3EventCounter.h"
#include "dataclasses/physics/I3EventHeader.h"

using std::ostringstream;

I3_MODULE(I3EventCounter);


I3EventCounter :: I3EventCounter(const I3Context& ctx) : I3Module(ctx)
{
  AddOutBox("OutBox");

  counterStep_ = 100;
  AddParameter("CounterStep",
               "Only print out event number if divisible by this",
	       counterStep_);

  dump_ = false;
  AddParameter("Dump",
               "Whether to dump the current frame to screen",
               dump_);

  nevents_ = 0;
  AddParameter("NEvents",
               "Number of events to process",
               nevents_);
}


void I3EventCounter :: Configure()
{

  GetParameter("CounterStep", counterStep_);
  log_info("(%s) Event Counter Step: %i",
           GetName().c_str(), counterStep_);

  GetParameter("Dump", dump_);
  log_info("(%s) Whether to dump frame to screen: %i",
           GetName().c_str(), dump_);

  GetParameter("NEvents", nevents_);
  log_info("(%s) NEvents: %i",
           GetName().c_str(), nevents_);

  count_ = 0;
}

static const char* myordinal(int i){
    static char ordinal[256];
    if ( ( (i%10) > 3 ) || ((i%10)==0) || (((i/10)%10)==1) ){
        sprintf(ordinal,"%dth",i);
    } else {
        switch(i%10){
            case 1:
                sprintf(ordinal,"%dst",i); break;
            case 2:
                sprintf(ordinal,"%dnd",i); break;
            case 3:
                sprintf(ordinal,"%drd",i); break;
            default:
                log_fatal("programming error i=%d",i);
        }
    }
    return ordinal;
}

void I3EventCounter :: Physics(I3FramePtr frame)
{
  count_++;
  const I3EventHeader &eh = frame->Get<I3EventHeader>("I3EventHeader");
  int evnum = eh.GetEventID();
  int runnum = eh.GetRunID();
  if (count_%counterStep_ == 0) {
    log_info("(%s) Processing %s event (EventID=%i, RunID=%i)",
             GetName().c_str(),myordinal(count_),evnum,runnum);
  }
  if (dump_) {
    ostringstream oss;
    oss << *frame;
    log_info("(%s) Current frame (%d):\n%s",
             GetName().c_str(), count_, oss.str().c_str() );
  }

  if (count_ >= nevents_ && nevents_ != 0) RequestSuspension();

  PushFrame(frame,"OutBox");
}


void I3EventCounter :: Finish()
{
  log_info("(%s) Total number of physics events:  %d",
           GetName().c_str(), count_);
}
