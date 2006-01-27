/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3EventOrigin.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3EVENTORIGIN_H
#define I3EVENTORIGIN_H

#include "dataclasses/StoragePolicy.h"
#include "dataclasses/I3Time.h"

class I3Frame;

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
  virtual void PopEvent(I3Frame& frame) = 0;
};

typedef shared_ptr<I3EventOrigin> I3EventOriginPtr;

#endif
