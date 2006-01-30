#ifndef I3EMPTYEVENTSERVICE_H
#define I3EMPTYEVENTSERVICE_H

#include "phys-services/I3EventService.h"

class I3EmptyEventService : public I3EventService
{
 public:
  I3EmptyEventService(int nFrames);
  bool MoreEvents() = 0;
  void PopEvent(I3Frame& frame) = 0;
 private:
  int nframes_;
  int currentCount_;
};

#endif
