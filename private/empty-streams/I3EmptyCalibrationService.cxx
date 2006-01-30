#include "phys-services/empty-streams/I3EmptyCalibrationService.h"

#include <dataclasses/calibration/I3Calibration.h>
#include <dataclasses/calibration/I3CalibrationHeader.h>

I3EmptyCalibrationService::I3EmptyCalibrationService()
{
  pair_.header = I3CalibrationHeaderPtr(new I3CalibrationHeader());
  pair_.header->SetStartTime(I3Time(0,0));
  pair_.header->SetEndTime(I3Time(3000,0));
  pair_.calibration = I3CalibrationPtr(new I3Calibration());
}

CalibrationPair I3EmptyCalibrationService::GetCalibration(I3Time time)
{
  return pair_;
}
