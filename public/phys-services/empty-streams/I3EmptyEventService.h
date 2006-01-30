#ifndef I3EMPTYEVENTSERVICE_H
#define I3EMPTYEVENTSERVICE_H

#include "phys-services/I3EventService.h"

class I3EmptyEventService : public I3EventService
{
 public:
  I3EmptyEventService(int nFrames);
  bool MoreEvents();
  void PopEvent(I3Frame& frame);
 private:
  int nframes_;
  int currentCount_;
};

#endif
