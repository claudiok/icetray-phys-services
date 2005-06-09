#ifndef I3DUMMYPHYSICSSOURCE_H
#define I3DUMMYPHYSICSSOURCE_H

#include "I3PhysicsSource.h"

class I3DummyPhysicsSource  : public I3PhysicsSource
{
 public:
  I3DummyPhysicsSource(I3Context& context);

  EventPair NextEvent();

  bool MoreEvents();

 private:
  int eventsReturned_;
  int maxEvents_;
};

#endif
