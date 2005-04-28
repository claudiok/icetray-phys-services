/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3EventOrigin.h
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#ifndef I3EVENTORIGIN_H
#define I3EVENTORIGIN_H

#include "dataclasses/I3Event.h"
#include "dataclasses/I3EventHeader.h"
#include "dataclasses/StoragePolicy.h"
#include "dataclasses/I3Time.h"

/**
 * @brief Dumb struct for holding an I3Event and its I3EventHeader
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
 * @brief This is the interface to classes which  
 * serve up an event and the time of the next 
 * event.  This is intended to be an icetray service
 */
class I3EventOrigin
{
 public:
  /**
   * @brief default name of this service in an icetray I3Context
   */
  static const char* DefaultName() { return "EventOrigin";}

  /**
   * @brief indicates whether or not there are more events to find.
   * 
   */
  virtual bool MoreEvents() = 0;
  virtual EventPair PopEvent() = 0;
};

typedef shared_ptr<I3EventOrigin> I3EventOriginPtr;

#endif
