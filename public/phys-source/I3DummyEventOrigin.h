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
  int maxEvents_;
  int currentEvent_;

 public:
  virtual ~I3DummyEventOrigin(){}

  I3DummyEventOrigin(int eventsToReturn);

  bool MoreEvents();

  EventPair PopEvent();
};

typedef PtrPolicy<I3DummyEventOrigin>::ThePolicy I3DummyEventOriginPtr;

#endif
