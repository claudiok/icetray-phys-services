#ifndef I3DUMMYPHYSICSSOURCE_H
#define I3DUMMYPHYSICSSOURCE_H

#include "I3PhysicsSource.h"

class I3DummyPhysicsSource  : public I3PhysicsSource
{
 public:
  I3DummyPhysicsSource(const I3Context& context);

  void Configure();

  EventPair NextEvent();

  bool MoreEvents();

 private:
  int eventsReturned_;
  int maxEvents_;
  bool mcEvents_;
};

#endif
