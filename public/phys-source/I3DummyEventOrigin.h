#ifndef I3DUMMYEVENTORIGIN_H
#define I3DUMMYEVENTORIGIN_H

#include "phys-source/I3EventOrigin.h"

/**
 * @brief a simple implementation of I3EventOrigin which
 * serves up ten (empty) events before quitting.
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3DummyEventOrigin : public I3EventOrigin
{
  I3Time currentTime_;
  I3Time maxTime_;

 public:
  virtual ~I3DummyEventOrigin(){}

  I3DummyEventOrigin() 
    {
      currentTime_.SetDaqTime(2005,0);
      maxTime_.SetDaqTime(2005,100000);
    }

  bool MoreEvents()
    {
      if(currentTime_ < maxTime_)
	return true;
      return false;
    }

  EventPair PopEvent()
    {
      EventPair e;
      e.event = I3EventPtr(new I3Event());
      e.header = I3EventHeaderPtr(new I3EventHeader());
      currentTime_.SetDaqTime(currentTime_.GetUTCYear(),
			      currentTime_.GetUTCDaqTime() + 10000);
      return e;
    };
  
  I3Time NextEventTime()
    {
      return currentTime_;
    }
};

typedef PtrPolicy<I3DummyEventOrigin>::ThePolicy I3DummyEventOriginPtr;

#endif
