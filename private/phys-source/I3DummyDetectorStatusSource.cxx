#include "phys-source/I3DummyDetectorStatusSource.h"


I3DummyDetectorStatusSource::I3DummyDetectorStatusSource(I3Context& context) 
  : I3DetectorStatusSource(context){}

DetectorStatusPair 
I3DummyDetectorStatusSource::GetDetectorStatus(I3Time eventTime)
{
  DetectorStatusPair toReturn;
  toReturn.header = I3DetectorStatusHeaderPtr(new I3DetectorStatusHeader());
  toReturn.header->SetStartTime(I3Time(0,0));
  toReturn.header->SetEndTime(I3Time(3000,0));
  toReturn.status = I3DetectorStatusPtr(new I3DetectorStatus());
  return toReturn;
}
