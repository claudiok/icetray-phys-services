#include "phys-source/I3XMLFileCalibrationSource.h"

I3XMLFileCalibrationSource::I3XMLFileCalibrationSource(I3Context& context) 
  : I3CalibrationSource(context)
{
    AddParameter("IceCubeCalibrationFile", "IceCube Calibration file",
		 ICCalibrationFile_);
}

void I3XMLFileCalibrationSource::Configure()
{
    GetParameter("IceCubeCalibrationFile",ICCalibrationFile_);
}

void I3XMLFileCalibrationSource::FillCalibration(I3Calibration& Calibration,
						       I3CalibrationHeader& CalibrationHeader)
{}

CalibrationPair 
I3XMLFileCalibrationSource::GetCalibration(I3Time eventTime)
{
    CalibrationPair toReturn;
    toReturn.header = I3CalibrationHeaderPtr(new I3CalibrationHeader());
    toReturn.header->SetStartTime(I3Time(0,0));
    toReturn.header->SetEndTime(I3Time(3000,0));
    toReturn.calibration = I3CalibrationPtr(new I3Calibration());
    return toReturn;
}
