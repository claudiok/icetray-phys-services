#ifndef I3GEOMETRYPAIR_H
#define I3GEOMETRYPAIR_H

#include "dataclasses/geometry/I3Geometry.h"
#include "dataclasses/geometry/I3GeometryHeader.h"

/**
 * @brief dumb struct for holding an I3Geometry and its I3GeometryHeader
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

#endif
