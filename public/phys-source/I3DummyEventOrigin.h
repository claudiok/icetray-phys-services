/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3DummyEventOrigin.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3DUMMYEVENTORIGIN_H
#define I3DUMMYEVENTORIGIN_H

#include "phys-source/I3EventOrigin.h"

/**
 * @brief a simple implementation of I3EventOrigin which
 * serves up ten (empty) events before quitting.
 */
class I3DummyEventOrigin : public I3EventOrigin
{
  int maxEvents_;
  int currentEvent_;
  bool mcEvents_;

 public:
  virtual ~I3DummyEventOrigin(){}

  I3DummyEventOrigin(int eventsToReturn);

  bool MoreEvents();

  void GiveMCEvents();

  void GiveNonMCEvents();

  EventPair PopEvent();
};

typedef shared_ptr<I3DummyEventOrigin> I3DummyEventOriginPtr;

#endif
