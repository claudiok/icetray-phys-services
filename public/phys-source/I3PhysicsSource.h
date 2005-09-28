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
#include "I3EventPair.h"

class I3PhysicsSource : public I3Source
{
 public:
  I3PhysicsSource(const I3Context& context);

  void Process();

  virtual EventPair NextEvent() = 0;
  
  virtual bool MoreEvents() = 0;

 private:
  void SendEvent();

  EventPair currentEvent_;
  

};

#endif
