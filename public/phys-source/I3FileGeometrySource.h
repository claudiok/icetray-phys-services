#ifndef I3FILEGEOMETRYSOURCE_H
#define I3FILEGEOMETRYSOURCE_H

#include "phys-source/I3GeometrySource.h"
#include "phys-source/I3FileGeoOrigin.h"

class I3FileGeometrySource : public I3GeometrySource
{
 public:
  I3FileGeometrySource(I3Context& context);

  void Configure();

  GeometryPair GetGeometry(I3Time eventTime);

 private:
  I3FileGeoOriginPtr origin_;

  string amaGeoFile_;
  string icecubeGeoFile_;
};

#endif
