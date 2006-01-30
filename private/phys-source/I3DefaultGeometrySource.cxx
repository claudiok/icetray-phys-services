#include "phys-services/source/I3DefaultGeometrySource.h"


I3_MODULE(I3DefaultGeometrySource);

I3DefaultGeometrySource::I3DefaultGeometrySource(const I3Context& context) 
  : I3GeometrySource(context){}

GeometryPair I3DefaultGeometrySource::GetGeometry(I3Time eventTime)
{
  GeometryPair toReturn;
  toReturn.geometry = I3GeometryPtr(new I3Geometry());
  toReturn.geometry->SetStartTime(I3Time(0,0));
  toReturn.geometry->SetEndTime(I3Time(3000,0));

  return toReturn;
}
