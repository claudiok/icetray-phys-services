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
#include "phys-source/I3TimeRange.h"

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

/**
 * @brief A module which fills the Geometry into the data stream
 * when it becomes outdated.
 * Looks at the I3GeometryOrigin service to accomplish this.
 *
 */
class I3GeometrySource : public I3PhysicsModule
{
 public:
  I3GeometrySource(I3Context& context);

  void Physics(I3Frame& frame);
  
  void Geometry(I3Frame& frame);

  void Calibration(I3Frame& frame);

  void DetectorStatus(I3Frame& frame);

  virtual GeometryPair GetGeometry(I3Time time)=0;
  
 private:
  void SendGeometry(I3Time time);
  
  bool IsGeometryCurrent(I3Time time);
  
  GeometryPair currentGeometry_;
  I3TimeRange currentGeometryRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
