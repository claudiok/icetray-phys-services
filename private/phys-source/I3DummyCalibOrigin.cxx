#include "phys-source/I3DummyCalibOrigin.h"

CalibrationPair I3DummyCalibOrigin::GetCalibration(I3Time time)
{
  CalibrationPair p;
  p.calibration = I3CalibPtr(new I3Calibration());
  p.header = I3CalibrationHeaderPtr(new I3CalibrationHeader());
  I3TimeRange range = GetCalibrationValidityRange(time);
  p.header->SetStartTime(range.lower);
  p.header->SetEndTime(range.upper);
  return p;
}

I3TimeRange I3DummyCalibOrigin::GetCalibrationValidityRange(I3Time time)
{
  I3Time lower;
  lower.SetDaqTime(0,0);
  I3Time upper;
  upper.SetDaqTime(3000,0);
  return I3TimeRange(lower,upper);
}
