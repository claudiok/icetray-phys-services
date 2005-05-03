/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3DummyMonitoringOrigin.cxx 7067 2005-04-28 15:04:38Z pretz $
 *
 * @file I3DummyMonitoringOrigin.cxx
 * @version $Revision:$
 * @date $Date: 2005-04-28 11:04:38 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */

#include "phys-source/I3DummyMonitoringOrigin.h"

I3DummyMonitoringOrigin::I3DummyMonitoringOrigin(int eventsToReturn)
{
  maxMonitorings_ = eventsToReturn;
  currentMonitoring_ = 0;
}

bool I3DummyMonitoringOrigin::MoreMonitorings()
{
  log_debug("current event %d of %d to send",
	    currentMonitoring_,
	    maxMonitorings_);
  if(currentMonitoring_ >= maxMonitorings_)
    return false;
  return true;
}

MonitoringPair I3DummyMonitoringOrigin::PopMonitoring()
{
  MonitoringPair e;
  e.monitoring = I3MonitoringPtr(new I3Monitoring());
  e.header = I3MonitoringHeaderPtr(new I3MonitoringHeader());

  I3Time eventTime;

  eventTime.SetDaqTime(2005,
		       0);

  e.header->SetStartTime(eventTime);
  e.header->SetEndTime(eventTime);

  currentMonitoring_++;

  return e;
}

