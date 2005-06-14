#include "phys-source/I3DummyGeometrySource.h"


I3DummyGeometrySource::I3DummyGeometrySource(I3Context& context) 
  : I3GeometrySource(context){}

GeometryPair I3DummyGeometrySource::GetGeometry(I3Time eventTime)
{
  GeometryPair toReturn;
  toReturn.header = I3GeometryHeaderPtr(new I3GeometryHeader());
  toReturn.header->SetStartTime(I3Time(0,0));
  toReturn.header->SetEndTime(I3Time(3000,0));
  toReturn.geometry = I3GeometryPtr(new I3Geometry());
  return toReturn;
}
