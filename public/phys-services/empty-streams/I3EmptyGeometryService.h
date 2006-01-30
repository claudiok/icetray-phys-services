#ifndef I3EMPTYGEOMETRYSERVICE_H
#define I3EMPTYGEOMETRYSERVICE_H

#include "phys-services/I3GeometryService.h"

class I3EmptyGeometryService : public I3GeometryService
{
 public:
  I3EmptyGeometryService();
  
  GeometryPair GetGeometry(I3Time time);

 private:

  GeometryPair pair_;
};

#endif
