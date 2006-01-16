#include "phys-services/source/I3DefaultMonitoringSource.h"

I3_MODULE(I3DefaultMonitoringSource);

I3DefaultMonitoringSource::I3DefaultMonitoringSource(const I3Context& context) : 
  I3MonitoringSource(context)
{
  monitoringsReturned_ = 0;
  maxMonitorings_ = 10;
}

MonitoringPair I3DefaultMonitoringSource::NextMonitoring()
{
  MonitoringPair toReturn;
  toReturn.header = I3MonitoringHeaderPtr(new I3MonitoringHeader());

  toReturn.header->SetStartTime(I3Time(2005,0));
  toReturn.monitoring = I3MonitoringPtr(new I3Monitoring());
  monitoringsReturned_++;
  return toReturn;
}

bool I3DefaultMonitoringSource::MoreMonitorings()
{
  if(monitoringsReturned_ < maxMonitorings_)
    return true;
  return false;
}
