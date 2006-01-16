#include "phys-services/source/I3DefaultCalibrationSource.h"


I3_MODULE(I3DefaultCalibrationSource);

I3DefaultCalibrationSource::I3DefaultCalibrationSource(const I3Context& context) 
  : I3CalibrationSource(context){}

CalibrationPair I3DefaultCalibrationSource::GetCalibration(I3Time eventTime)
{
  CalibrationPair toReturn;
  toReturn.header = I3CalibrationHeaderPtr(new I3CalibrationHeader());
  toReturn.header->SetStartTime(I3Time(0,0));
  toReturn.header->SetEndTime(I3Time(3000,0));
  toReturn.calibration = I3CalibrationPtr(new I3Calibration());
  return toReturn;
}
