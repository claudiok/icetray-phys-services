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

  I3DummyEventOrigin();

  bool MoreEvents();

  EventPair PopEvent();
  
  I3Time NextEventTime();
};

typedef PtrPolicy<I3DummyEventOrigin>::ThePolicy I3DummyEventOriginPtr;

#endif
