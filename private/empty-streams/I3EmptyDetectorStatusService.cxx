#include "phys-services/empty-streams/I3EmptyDetectorStatusService.h"

#include <dataclasses/status/I3DetectorStatus.h>
#include <dataclasses/status/I3DetectorStatusHeader.h>

I3EmptyDetectorStatusService::I3EmptyDetectorStatusService()
{
  pair_.header = I3DetectorStatusHeaderPtr(new I3DetectorStatusHeader());
  pair_.header->SetStartTime(I3Time(0,0));
  pair_.header->SetEndTime(I3Time(3000,0));
  pair_.status = I3DetectorStatusPtr(new I3DetectorStatus());
}

DetectorStatusPair I3EmptyDetectorStatusService::GetDetectorStatus(I3Time time)
{
  return pair_;
}
