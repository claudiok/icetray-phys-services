#ifndef I3DUMMYEVENTORIGIN_H
#define I3DUMMYEVENTORIGIN_H

#include "phys-source/I3EventOrigin.h"

/**
 * @brief a simple implementation of I3EventOrigin which
 * serves up ten (empty) events before quitting.
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
class I3DummyEventOrigin : public I3EventOrigin
{
  Time currentTime_;


 public:
  I3DummyEventOrigin() : currentTime_(0.0){}

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

typedef PtrPolicy<I3DummyEventOrigin>::ThePolicy I3DummyEventOriginPtr;

#endif
