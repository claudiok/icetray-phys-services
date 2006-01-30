#include "phys-services/empty-streams/I3EmptyCalibrationService.h"

#include <dataclasses/calibration/I3Calibration.h>

I3EmptyCalibrationService::I3EmptyCalibrationService()
{
  calibration_ = I3CalibrationPtr(new I3Calibration());
  calibration_->SetStartTime(I3Time(0,0));
  calibration_->SetEndTime(I3Time(3000,0));

}

I3CalibrationPtr I3EmptyCalibrationService::GetCalibration(I3Time time)
{
  return calibration_;
}
