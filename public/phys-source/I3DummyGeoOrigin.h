#ifndef I3DUMMYGEOORIGIN_H
#define I3DUMMYGEOORIGIN_H

#include "phys-source/I3GeometryOrigin.h"
#include <cmath>
/**
 * @brief A simple implemetation of the I3GeometryOrigin which serves
 * up one (empty) geometry
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3DummyGeoOrigin : public I3GeometryOrigin
{
 public:
  GeometryPair GetGeometry(Time time)
    {
      GeometryPair p;
      p.geometry = I3GeometryPtr(new I3Geometry());
      p.header = I3GeometryHeaderPtr(new I3GeometryHeader());
      return p;
    }
  
  TimeRange GetGeometryValidityRange(Time time)
    {
      return TimeRange(-INFINITY,INFINITY);
    }
};
 
typedef PtrPolicy<I3DummyGeoOrigin>::ThePolicy I3DummyGeoOriginPtr;

#endif
