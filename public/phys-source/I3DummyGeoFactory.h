#ifndef SIMPLEGEOFACTORY_H
#define SIMPLEGEOFACTORY_H

#include "phys-source/I3GeometryFactory.h"
#include <cmath>
/**
 * @brief A simple implemetation of the I3GeometryFactory which serves
 * up one (empty) geometry
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
class I3DummyGeoFactory : public I3GeometryFactory
{
  double nextTime_;
 public:
  GeometryPair GetGeometry(Time time)
    {
      GeometryPair p;
      p.geometry = I3GeometryPtr(new I3Geometry());
      p.header = I3GeometryHeaderPtr(new I3GeometryHeader());
      nextTime_ = INFINITY;
      return p;
    }
  
  Time NextGeometryTime()
    {
      return nextTime_;
    }

  I3DummyGeoFactory() : nextTime_(-INFINITY){}



};
 
typedef PtrPolicy<I3DummyGeoFactory>::ThePolicy I3DummyGeoFactoryPtr;

#endif
