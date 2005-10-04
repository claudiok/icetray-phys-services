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

/**
 * @brief The base class for source modules which sends out an I3Event 
 *
 * Two virtual methods must be implemented by deriving classes to customize
 * the behavior.
 */
class I3PhysicsSource : public I3Source
{
 public:
  I3PhysicsSource(const I3Context& context);

  void Process();

  /**
   * @brief This method should only be called when
   * I3PhysicsSource::MoreEvents() is returning true.  The returned
   * EventPair.header should have a valid start time. 
   *
   * This method should allocate a new I3Event and a new I3EventHeader and
   * return it filled as the module would like
   */
  virtual EventPair NextEvent() = 0;
  
  /**
   * @brief IceTray will continue to run and call I3PhysicsSource::NextEvent()
   * until this method returns false
   */
  virtual bool MoreEvents() = 0;

  SET_LOGGER("I3PhysicsSource");

 private:
  void SendEvent();

  EventPair currentEvent_;
  

};

#endif
