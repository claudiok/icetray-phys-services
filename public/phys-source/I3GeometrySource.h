/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3GeometrySource.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3GEOMETRYSOURCE_H
#define I3GEOMETRYSOURCE_H

#include "phys-services/I3PhysicsModule.h"
#include "phys-source/I3GeometryOrigin.h"
#include "phys-source/I3TimeRange.h"

/**
 * @brief A module which fills the Geometry into the data stream
 * when it becomes outdated.
 *
 */
class I3GeometrySource : public I3PhysicsModule
{
 public:
  I3GeometrySource(I3Context& context);

  void Physics(I3Frame& frame);
  
  void Geometry(I3Frame& frame);

  /**
   * virtual, but should only be implemented if you want to change
   * the logic for when the geometry is updated
   */
  virtual bool ShouldUpdateGeometry(I3Frame& frame);

  /**
   * Give me the geometry that should be in this frame
   */
  virtual GeometryPair GetGeometry(I3Frame& frame,I3Time eventTime) = 0;

 private:
  void CurrentGeometryIntoFrame(I3Frame& frame);

  GeometryPair currentGeometry_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
