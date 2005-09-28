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
#include "I3GeometryPair.h"
#include "services/I3Boxes.h"

/**
 * @brief A module which fills the Geometry into the data stream
 * when it becomes outdated.
 * Looks at the I3GeometryOrigin service to accomplish this.
 *
 */
class I3GeometrySource : public I3PhysicsModule
{
 public:
  I3GeometrySource(const I3Context& context);

  void Process();

  virtual GeometryPair GetGeometry(I3Time time)=0;

  virtual bool IsGeometryCurrent(I3Time time);
  
 private:
  I3Boxes& GetBoxes();

  void SendGeometry(I3Time time);
    
  GeometryPair currentGeometry_;
  I3TimeRange currentGeometryRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
