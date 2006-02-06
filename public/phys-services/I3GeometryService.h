/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3GeometryService.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3GEOMETRYSERVICE_H
#define I3GEOMETRYSERVICE_H

#include "phys-services/I3TimeRange.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "dataclasses/Utility.h"

/**
 * @brief This is an interface to classes which generates I3Geometry and
 * I3GeometryHeader objects given an I3Time.
 * This is intended to be an icetray services for getting the geometry
 * information into the system
 */
class I3GeometryService
{
 public:
  /**
   * @brief This is the default name of the service in an I3Context
   */
  static const char* DefaultName() { return "GeometryService";}

  /**
   * @brief gives the I3Geometry and I3GeometryHeader for the
   * indicated time.
   */
  virtual I3GeometryPtr GetGeometry(I3Time time) = 0;
};

typedef shared_ptr<I3GeometryService> I3GeometryServicePtr;


#endif
