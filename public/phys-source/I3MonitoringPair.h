#ifndef I3MONITORINGPAIR_H
#define I3MONITORINGPAIR_H

#include "dataclasses/I3Monitoring.h"
#include "dataclasses/I3MonitoringHeader.h"


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

#endif
