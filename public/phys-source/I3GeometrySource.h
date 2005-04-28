/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3GeometrySource.h
 * @version $Revision:$
 * @date $Date:$
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
  
 private:
  void SendGeometry(I3Time time);
  
  bool IsGeometryCurrent(I3Time time);
  
  I3GeometryOrigin& GetGeometryFactory();
  
  GeometryPair currentGeometry_;
  I3TimeRange currentGeometryRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
