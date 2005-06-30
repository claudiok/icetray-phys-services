#include "phys-source/I3DefaultGeometrySource.h"


I3DefaultGeometrySource::I3DefaultGeometrySource(I3Context& context) 
  : I3GeometrySource(context){}

GeometryPair I3DefaultGeometrySource::GetGeometry(I3Time eventTime)
{
  GeometryPair toReturn;
  toReturn.header = I3GeometryHeaderPtr(new I3GeometryHeader());
  toReturn.header->SetStartTime(I3Time(0,0));
  toReturn.header->SetEndTime(I3Time(3000,0));
  toReturn.geometry = I3GeometryPtr(new I3Geometry());
  return toReturn;
}
