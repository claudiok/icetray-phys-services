#ifndef I3EVENTORIGIN_H
#define I3EVENTORIGIN_H

#include "Time.h"
#include "dataclasses/I3Event.h"
#include "dataclasses/I3EventHeader.h"
#include "dataclasses/StoragePolicy.h"

/**
 * @brief Dumb struct for holding an I3Event and its I3EventHeader
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
struct EventPair
{
  I3EventPtr event;
  I3EventHeaderPtr header;

  operator bool()
  {
    if(event && header)
      return true;
    return false;
  }
};

/**
 * @brief This class serves up an event and the time of the next 
 * event.
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
class I3EventOrigin
{
 public:
  static const char* DefaultName() { return "EventOrigin";}
  virtual bool MoreEvents() = 0;
  virtual EventPair PopEvent() = 0;
  virtual Time NextEventTime() = 0;
};

typedef PtrPolicy<I3EventOrigin>::ThePolicy I3EventOriginPtr;

#endif
