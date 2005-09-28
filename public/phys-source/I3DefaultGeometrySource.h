#ifndef I3DEFAULTGEOMETRYSOURCE_H
#define I3DEFAULTGEOMETRYSOURCE_H

#include "I3GeometrySource.h"

class I3DefaultGeometrySource : public I3GeometrySource
{
 public:
  I3DefaultGeometrySource(const I3Context& context);

  GeometryPair GetGeometry(I3Time eventTime);


};


#endif
