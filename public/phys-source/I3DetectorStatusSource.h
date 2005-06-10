/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3DetectorStatusSource.h 7057 2005-04-28 13:58:02Z pretz $
 *
 * @file I3DetectorStatusSource.h
 * @version $Revision:$
 * @date $Date: 2005-04-28 09:58:02 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */

#ifndef I3DETECTORSTATUSSOURCE_H
#define I3DETECTORSTATUSSOURCE_H

#include "phys-services/I3PhysicsModule.h"

/**
 * @brief Dumb struct for holding an I3DetectorStatus and its 
 * I3DetectorStatusHeader
 */
struct DetectorStatusPair
{
  I3DetectorStatusPtr status;
  I3DetectorStatusHeaderPtr header;

  operator bool()
  {
    if(status && header)
      return true;
    return false;
  }
};

/**
 * @brief A module which fills the DetectorStatus into the data stream
 * when it becomes outdated.
 *
 */
class I3DetectorStatusSource : public I3PhysicsModule
{
 public:
  I3DetectorStatusSource(I3Context& context);

  void Physics(I3Frame& frame);
  
  void DetectorStatus(I3Frame& frame);

  /**
   * virtual, but should only be implemented if you want to change
   * the logic for when the geometry is updated
   */
  virtual bool ShouldUpdateDetectorStatus(I3Frame& frame);

  /**
   * Give me the geometry that should be in this frame
   */
  virtual DetectorStatusPair GetDetectorStatus(I3Frame& frame,
					       I3Time eventTime) = 0;

 private:
  void CurrentDetectorStatusIntoFrame(I3Frame& frame);

  DetectorStatusPair currentDetectorStatus_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
