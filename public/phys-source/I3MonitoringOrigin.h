/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3MonitoringOrigin.h 7057 2005-04-28 13:58:02Z pretz $
 *
 * @file I3MonitoringOrigin.h
 * @version $Revision:$
 * @date $Date: 2005-04-28 09:58:02 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */

#ifndef I3MONITORINGORIGIN_H
#define I3MONITORINGORIGIN_H

#include "dataclasses/I3Monitoring.h"
#include "dataclasses/I3MonitoringHeader.h"
#include "dataclasses/StoragePolicy.h"
#include "dataclasses/I3Time.h"

/**
 * @brief Dumb struct for holding an I3Monitoring and its I3MonitoringHeader
 */
struct MonitoringPair
{
  I3MonitoringPtr monitoring;
  I3MonitoringHeaderPtr header;

  operator bool()
  {
    if(monitoring && header)
      return true;
    return false;
  }
};

/**
 * @brief This is the interface to classes which  
 * serve up an event and the time of the next 
 * event.  This is intended to be an icetray service
 */
class I3MonitoringOrigin
{
 public:
  /**
   * @brief default name of this service in an icetray I3Context
   */
  static const char* DefaultName() { return "MonitoringOrigin";}

  /**
   * @brief indicates whether or not there are more events to find.
   * 
   */
  virtual bool MoreMonitorings() = 0;
  virtual MonitoringPair PopMonitoring() = 0;
};

typedef shared_ptr<I3MonitoringOrigin> I3MonitoringOriginPtr;

#endif
