#ifndef I3DUMMYGEOMETRYSOURCE_H
#define I3DUMMYGEOMETRYSOURCE_H

#include "I3GeometrySource.h"

class I3DummyGeometrySource : public I3GeometrySource
{
 public:
  I3DummyGeometrySource(I3Context& context);

  GeometryPair GetGeometry(I3Frame& frame,I3Time eventTime);


};


#endif
