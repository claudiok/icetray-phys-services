#ifndef I3GEOMETRYFACTORY_H
#define I3GEOMETRYFACTORY_H

#include "Time.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3GeometryHeader.h"
#include "dataclasses/StoragePolicy.h"

/**
 * @brief dumb struct for holding an I3Geometry and its I3GeometryHeader
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
struct GeometryPair
{
  I3GeometryPtr geometry;
  I3GeometryHeaderPtr header;

  operator bool()
  {
    if(geometry && header)
      return true;
    return false;
  }
};

/**
 * @brief This class generates I3Geometry objects given a time
 * and then tells the next time the geometry changes.
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
class I3GeometryFactory
{
 public:
  static const char* DefaultName() { return "GeometryFactory";}
  virtual GeometryPair GetGeometry(Time time) = 0;
  virtual Time NextGeometryTime() = 0;
};

typedef PtrPolicy<I3GeometryFactory>::ThePolicy I3GeometryFactoryPtr;


#endif
