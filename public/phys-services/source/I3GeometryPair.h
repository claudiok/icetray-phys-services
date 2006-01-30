#ifndef I3GEOMETRYPAIR_H
#define I3GEOMETRYPAIR_H

#include "dataclasses/geometry/I3Geometry.h"

/**
 * @brief dumb struct for holding an I3Geometry and its I3GeometryHeader
 */
struct GeometryPair
{
  I3GeometryPtr geometry;

  operator bool()
  {
    if(geometry)
      return true;
    return false;
  }
};

#endif
