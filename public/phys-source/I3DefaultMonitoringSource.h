#ifndef I3DEFAULTMONITORINGSOURCE_H
#define I3DEFAULTMONITORINGSOURCE_H

#include "I3MonitoringSource.h"

class I3DefaultMonitoringSource  : public I3MonitoringSource
{
 public:
  I3DefaultMonitoringSource(I3Context& context);

  MonitoringPair NextMonitoring();

  bool MoreMonitorings();

 private:
  int monitoringsReturned_;
  int maxMonitorings_;
};

#endif
