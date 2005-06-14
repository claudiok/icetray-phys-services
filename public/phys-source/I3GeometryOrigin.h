/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3GeometryOrigin.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3GEOMETRYORIGIN_H
#define I3GEOMETRYORIGIN_H

#include "I3TimeRange.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3GeometryHeader.h"
#include "dataclasses/StoragePolicy.h"
#include "I3GeometryPair.h"

/**
 * @brief This is an interface to classes which generates I3Geometry and
 * I3GeometryHeader objects given an I3Time.
 * This is intended to be an icetray services for getting the geometry
 * information into the system
 */
class I3GeometryOrigin
{
 public:
  /**
   * @brief This is the default name of the service in an I3Context
   */
  static const char* DefaultName() { return "GeometryOrigin";}

  /**
   * @brief gives the I3Geometry and I3GeometryHeader for the
   * indicated time.
   */
  virtual GeometryPair GetGeometry(I3Time time) = 0;
};

typedef shared_ptr<I3GeometryOrigin> I3GeometryOriginPtr;


#endif
