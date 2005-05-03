/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3DummyMonitoringOrigin.h 7057 2005-04-28 13:58:02Z pretz $
 *
 * @file I3DummyMonitoringOrigin.h
 * @version $Revision:$
 * @date $Date: 2005-04-28 09:58:02 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */

#ifndef I3DUMMYEVENTORIGIN_H
#define I3DUMMYEVENTORIGIN_H

#include "phys-source/I3MonitoringOrigin.h"

/**
 * @brief a simple implementation of I3MonitoringOrigin which
 * serves up ten (empty) events before quitting.
 */
class I3DummyMonitoringOrigin : public I3MonitoringOrigin
{
  int maxMonitorings_;
  int currentMonitoring_;

 public:
  virtual ~I3DummyMonitoringOrigin(){}

  I3DummyMonitoringOrigin(int eventsToReturn);

  bool MoreMonitorings();

  MonitoringPair PopMonitoring();
};

typedef shared_ptr<I3DummyMonitoringOrigin> I3DummyMonitoringOriginPtr;

#endif
