#ifndef I3EMPTYEVENTSERVICE_H
#define I3EMPTYEVENTSERVICE_H

#include <dataclasses/I3Time.h>
#include "interfaces/I3EventService.h"

class I3EmptyEventService : public I3EventService
{
 public:
  I3EmptyEventService(int nFrames, I3Time theTime, unsigned theRun);

  virtual ~I3EmptyEventService();

  bool MoreEvents();

  I3Time PopEvent(I3Frame& frame);

 private:
  int nframes_;
  int currentCount_;
  I3Time eventTime_;
  unsigned runNumber_;
};

#endif
