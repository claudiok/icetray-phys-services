#include <sstream>
#include <fstream>
#include "phys-services/I3EventCounter.h"
#include "dataclasses/physics/I3EventHeader.h"

using std::ostringstream;

I3_MODULE(I3EventCounter);


I3EventCounter :: I3EventCounter(const I3Context& ctx) : 
		I3Module(ctx),
		physCount_(0),
		statusCount_(0),
		geometryCount_(0),
		calibCount_(0),
		counterStep_(100),
		nevents_(0),
		dump_(false)
{
  AddOutBox("OutBox");

  path_="stdout";
  AddParameter("filename","The file we'll write to or ('stdout' | 'stderr').  ", path_);

  fmt_ ="physics frames: %d\n"; 
  fmt_+="geometry frames: %d\n"; 
  fmt_+="calibration frames: %d\n";
  fmt_+=" detector status frames: %d\n";
  AddParameter("formatstr","Format string for frame counts.  ", fmt_);

  AddParameter("CounterStep",
               "Only print out event number if divisible by this",
	       counterStep_);

  AddParameter("Dump",
               "Whether to dump the current frame to screen",
               dump_);

  AddParameter("NEvents",
               "Number of events to process",
               nevents_);
}


void I3EventCounter :: Configure()
{
  GetParameter("filename", path_);
  log_info("(%s) Writting event count to : %s",
           GetName().c_str(), path_.c_str());

  GetParameter("formatstr", fmt_);
  log_info("(%s) : %s",
           GetName().c_str(), fmt_.c_str());

  GetParameter("CounterStep", counterStep_);
  log_info("(%s) Event Counter Step: %i",
           GetName().c_str(), counterStep_);

  GetParameter("Dump", dump_);
  log_info("(%s) Whether to dump frame to screen: %i",
           GetName().c_str(), dump_);

  GetParameter("NEvents", nevents_);
  log_info("(%s) NEvents: %i",
           GetName().c_str(), nevents_);

  if (path_ == "stdout") {
	  out = &std::cout;
  }
  else if (path_ == "stderr") {
	  out = &std::cerr;
  }
  else {
	  out = new ofstream(path_.c_str(), ios::out);
  }
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
  physCount_++;

  I3EventHeaderConstPtr eh = frame->Get<I3EventHeaderConstPtr>("I3EventHeader");
  if (eh) {  // Frame might not have an event header
	  int evnum = eh->GetEventID();
	  int runnum = eh->GetRunID();
	  if (physCount_%counterStep_ == 0) {
		log_info("(%s) Processing %s event (EventID=%i, RunID=%i)",
				 GetName().c_str(),myordinal(physCount_),evnum,runnum);
	  }
  }

  if (dump_) {
    ostringstream oss;
    oss << *frame;
    log_info("(%s) Current frame (%d):\n%s",
             GetName().c_str(), physCount_, oss.str().c_str() );
  }

  if (physCount_ >= nevents_ && nevents_ != 0) RequestSuspension();

  PushFrame(frame,"OutBox");
}

void I3EventCounter::Geometry(I3FramePtr frame)
{
  geometryCount_++;  
  log_debug("frame %d", geometryCount_);  

  PushFrame(frame,"OutBox");
}

void I3EventCounter::Calibration(I3FramePtr frame)
{
  calibCount_++;  
  log_debug("frame %d", calibCount_);  

  PushFrame(frame,"OutBox");
}

void I3EventCounter::DetectorStatus(I3FramePtr frame)
{
  statusCount_++;  
  log_debug("frame %d", statusCount_);  

  PushFrame(frame,"OutBox");
}


void I3EventCounter :: Finish()
{
  log_info("(%s) Total number of physics events:  %d",
           GetName().c_str(), physCount_);

  // format string with values
  sprintf(buffer,fmt_.c_str(),physCount_,geometryCount_,calibCount_,statusCount_);

  // out put string to stream
  (*out) << buffer << endl;
}
