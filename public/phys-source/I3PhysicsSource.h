/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3PhysicsSource.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3PHYSICSSOURCE_H
#define I3PHYSICSSOURCE_H

#include "dataclasses/I3Event.h"
#include "dataclasses/I3EventHeader.h"

#include "icetray/I3Source.h"

#include "I3EventOrigin.h"

/**
 * @brief An icetray module which fills the data stream with an event.
 * This is an I3Source and should be first in the list
 */
class I3PhysicsSource : public I3Source
{
 public:
  I3PhysicsSource(I3Context& context);

  void Process();

  virtual EventPair NextEvent() = 0;

  virtual bool MoreEvents() = 0;

 private:
  void SendEvent();

};

#endif
