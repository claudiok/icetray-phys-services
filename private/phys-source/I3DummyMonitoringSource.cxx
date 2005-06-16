#include "phys-source/I3DummyMonitoringSource.h"

I3DummyMonitoringSource::I3DummyMonitoringSource(I3Context& context) : 
  I3MonitoringSource(context)
{
  monitoringsReturned_ = 0;
  maxMonitorings_ = 10;
}

MonitoringPair I3DummyMonitoringSource::NextMonitoring()
{
  MonitoringPair toReturn;
  toReturn.header = I3MonitoringHeaderPtr(new I3MonitoringHeader());

  toReturn.header->SetStartTime(I3Time(2005,0));
  toReturn.monitoring = I3MonitoringPtr(new I3Monitoring());
  monitoringsReturned_++;
  return toReturn;
}

bool I3DummyMonitoringSource::MoreMonitorings()
{
  if(monitoringsReturned_ < maxMonitorings_)
    return true;
  return false;
}
