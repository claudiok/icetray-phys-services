#include "phys-source/I3DummyDetectorStatusOrigin.h"

DetectorStatusPair I3DummyDetectorStatusOrigin::GetDetectorStatus(I3Time time)
{
  DetectorStatusPair p;
  p.status = I3DetectorStatusPtr(new I3DetectorStatus());
  p.header = I3DetectorStatusHeaderPtr(new I3DetectorStatusHeader());

  I3Time lower;
  lower.SetDaqTime(0,0);
  I3Time upper;
  upper.SetDaqTime(3000,0);

  p.header->SetStartTime(lower);
  p.header->SetEndTime(upper);
  return p;
}

