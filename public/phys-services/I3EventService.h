/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3EventService.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3EVENTSERVICE_H
#define I3EVENTSERVICE_H

#include <icetray/I3FrameObject.h>
#include <icetray/I3DefaultName.h>

#include "dataclasses/Utility.h"
#include "dataclasses/I3Time.h"

class I3Frame;

/**
 * @brief This is the interface to classes which  
 * serve up an event and the time of the next 
 * event.  This is intended to be an icetray service
 */
class I3EventService
{
 public:

  /**
   * @brief indicates whether or not there are more events to find.
   * 
   */
  virtual bool MoreEvents() = 0;

  /**
   * @brief This method should fill the frame with all the relevent
   * frame data.  Returned is the time of the event.
   */
  virtual I3Time PopEvent(I3Frame& frame) = 0;

  virtual ~I3EventService() { }
};

I3_DEFAULT_NAME(I3EventService);
I3_POINTER_TYPEDEFS(I3EventService);

#endif
