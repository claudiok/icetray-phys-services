#ifndef I3DUMMYEVENTFACTORY_H
#define I3DUMMYEVENTFACTORY_H

#include "phys-source/I3EventFactory.h"

/**
 * @brief a simple implementation of I3EventFactory which
 * serves up ten (empty) events before quitting.
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
class I3DummyEventFactory : public I3EventFactory
{
  Time currentTime_;


 public:
  I3DummyEventFactory() : currentTime_(0.0){}

  bool MoreEvents()
    {
      if(currentTime_ < 10.0)
	return true;
      return false;
    }

  EventPair PopEvent()
    {
      EventPair e;
      e.event = I3EventPtr(new I3Event());
      e.header = I3EventHeaderPtr(new I3EventHeader());
      currentTime_ += 1.0;
      return e;
    };
  
  Time NextEventTime()
    {
      return currentTime_;
    }
};

typedef PtrPolicy<I3DummyEventFactory>::ThePolicy I3DummyEventFactoryPtr;

#endif
