#include "phys-source/I3FileGeometrySource.h"

I3FileGeometrySource::I3FileGeometrySource(I3Context& context) :
  I3GeometrySource(context)
{
  AddParameter("AmandaGeoFile",
	       "Geometry file for the AMANDA detector",
	       amaGeoFile_);
  AddParameter("IceCubeGeoFile",
	       "Geometry file for the IceCube detector",
	       icecubeGeoFile_);
}

void I3FileGeometrySource::Configure()
{
  GetParameter("AmandaGeoFile",amaGeoFile_);
  GetParameter("IceCubeGeoFile",icecubeGeoFile_);
  
  origin_ = I3FileGeoOriginPtr(new I3FileGeoOrigin(amaGeoFile_,
						   icecubeGeoFile_));
}

GeometryPair I3FileGeometrySource::GetGeometry(I3Time eventTime)
{
  return origin_->GetGeometry(eventTime);
}
