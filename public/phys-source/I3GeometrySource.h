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
 *
 * Users are expected to override the 
 * I3GeometrySource::GetGeometry(I3Time time) to get their
 * Geometry data into icetray.
 * 
 * Optionally people writing subclasses of I3GeometrySource can 
 * override the I3GeometrySource::IsGeometryCurrent(I3Time time)
 * method and change the logic that is used when deciding when to 
 * send out a new Geometry.  The default behavior is to use
 * the StartTime and EndTime of the last Geometry sent
 */
class I3GeometrySource : public I3PhysicsModule
{
 public:
  I3GeometrySource(const I3Context& context);

  void Process();

  /**
   * This method should be written to return a newly allocated
   * I3Geometry and I3GeometryHeader for the given
   * time.  The start time and end time of the header should be
   * valid.
   */
  virtual GeometryPair GetGeometry(I3Time time)=0;

  /**
   * Called internally to check whether the last Geometry sent out
   * is current or not by looking at the StartTime and end time on the
   * last Geometry.  Can be overridden to change this behavior
   */
  virtual bool IsGeometryCurrent(I3Time time);
  
 private:
  I3Boxes& GetBoxes();

  void SendGeometry(I3Time time);
    
  GeometryPair currentGeometry_;
  I3TimeRange currentGeometryRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
