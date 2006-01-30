#include "phys-services/empty-streams/I3EmptyDetectorStatusService.h"

#include <dataclasses/status/I3DetectorStatus.h>

I3EmptyDetectorStatusService::I3EmptyDetectorStatusService()
{
  status_ = I3DetectorStatusPtr(new I3DetectorStatus());
  status_->SetStartTime(I3Time(0,0));
  status_->SetEndTime(I3Time(3000,0));

}

I3DetectorStatusPtr I3EmptyDetectorStatusService::GetDetectorStatus(I3Time time)
{
  return status_;
}
