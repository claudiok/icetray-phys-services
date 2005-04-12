#ifndef I3GEOMETRYORIGIN_H
#define I3GEOMETRYORIGIN_H

#include "I3TimeRange.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3GeometryHeader.h"
#include "dataclasses/StoragePolicy.h"

/**
 * @brief dumb struct for holding an I3Geometry and its I3GeometryHeader
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
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
 * @ingroup experimentalphysservices
 */
class I3GeometryOrigin
{
 public:
  static const char* DefaultName() { return "GeometryOrigin";}
  virtual GeometryPair GetGeometry(I3Time time) = 0;
};

typedef shared_ptr<I3GeometryOrigin> I3GeometryOriginPtr;


#endif
