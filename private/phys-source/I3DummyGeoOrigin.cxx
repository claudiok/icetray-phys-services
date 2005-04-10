#include "phys-source/I3DummyGeoOrigin.h"

GeometryPair I3DummyGeoOrigin::GetGeometry(I3Time time)
{
  GeometryPair p;
  p.geometry = I3GeometryPtr(new I3Geometry());
  p.header = I3GeometryHeaderPtr(new I3GeometryHeader());

  I3Time lower;
  lower.SetDaqTime(0,0);
  I3Time upper;
  upper.SetDaqTime(3000,0);

  p.header->SetStartTime(lower);
  p.header->SetEndTime(upper);
  return p;
}

