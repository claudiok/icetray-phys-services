#ifndef I3DEFAULTPHYSICSSOURCE_H
#define I3DEFAULTPHYSICSSOURCE_H

#include "I3PhysicsSource.h"

class I3DefaultPhysicsSource  : public I3PhysicsSource
{
 public:
  I3DefaultPhysicsSource(const I3Context& context);

  void Configure();

  EventPair NextEvent();

  bool MoreEvents();

 private:
  int eventsReturned_;
  int maxEvents_;
  bool mcEvents_;
};

#endif
