#include "phys-services/source/I3DefaultDetectorStatusSource.h"


I3_MODULE(I3DefaultDetectorStatusSource);

I3DefaultDetectorStatusSource::I3DefaultDetectorStatusSource(const I3Context& context) 
  : I3DetectorStatusSource(context){}

DetectorStatusPair 
I3DefaultDetectorStatusSource::GetDetectorStatus(I3Time eventTime)
{
  DetectorStatusPair toReturn;
  toReturn.status = I3DetectorStatusPtr(new I3DetectorStatus());
  toReturn.status->SetStartTime(I3Time(0,0));
  toReturn.status->SetEndTime(I3Time(3000,0));

  return toReturn;
}
