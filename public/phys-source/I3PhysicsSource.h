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

class I3PhysicsSource : public I3Source
{
 public:
  I3PhysicsSource(I3Context& context);

  void Process();

  virtual EventPair NextEvent() = 0;
  
  virtual bool MoreEvents() = 0;

 private:
  void SendEvent();

  EventPair currentEvent_;
  

};

#endif
