#ifndef I3DUMMYMONITORINGSOURCE_H
#define I3DUMMYMONITORINGSOURCE_H

#include "I3MonitoringSource.h"

class I3DummyMonitoringSource  : public I3MonitoringSource
{
 public:
  I3DummyMonitoringSource(const I3Context& context);

  MonitoringPair NextMonitoring();

  bool MoreMonitorings();

 private:
  int monitoringsReturned_;
  int maxMonitorings_;
};

#endif
