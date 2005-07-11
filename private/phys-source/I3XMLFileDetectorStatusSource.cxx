#include "phys-source/I3XMLFileDetectorStatusSource.h"

I3XMLFileDetectorStatusSource::I3XMLFileDetectorStatusSource(I3Context& context) 
  : I3DetectorStatusSource(context)
{
    AddParameter("IceCubeDetectorStatusFile", "IceCube DetectorStatus file",
		 ICDetectorStatusFile_);
}

void I3XMLFileDetectorStatusSource::Configure()
{
    GetParameter("IceCubeDetectorStatusFile",ICDetectorStatusFile_);
}

void I3XMLFileDetectorStatusSource::FillDetectorStatus(I3DetectorStatus& DetectorStatus,
						       I3DetectorStatusHeader& DetectorStatusHeader)
{}

DetectorStatusPair 
I3XMLFileDetectorStatusSource::GetDetectorStatus(I3Time eventTime)
{
    DetectorStatusPair toReturn;
    toReturn.header = I3DetectorStatusHeaderPtr(new I3DetectorStatusHeader());
    toReturn.header->SetStartTime(I3Time(0,0));
    toReturn.header->SetEndTime(I3Time(3000,0));
    toReturn.status = I3DetectorStatusPtr(new I3DetectorStatus());
    return toReturn;
}
