#include "phys-services/empty-streams/I3EmptyGeometryService.h"

#include <dataclasses/geometry/I3Geometry.h>
#include <dataclasses/geometry/I3GeometryHeader.h>

I3EmptyGeometryService::I3EmptyGeometryService()
{
  pair_.header = I3GeometryHeaderPtr(new I3GeometryHeader());
  pair_.header->SetStartTime(I3Time(0,0));
  pair_.header->SetEndTime(I3Time(3000,0));
  pair_.geometry = I3GeometryPtr(new I3Geometry());
}

GeometryPair I3EmptyGeometryService::GetGeometry(I3Time time)
{
  return pair_;
}
