/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3DetectorStatusSource.h
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#ifndef I3DETECTORSTATUSSOURCE_H
#define I3DETECTORSTATUSSOURCE_H

#include "phys-services/I3PhysicsModule.h"
#include "phys-source/I3TimeRange.h"
#include "services/I3Boxes.h"
#include "I3DetectorStatusPair.h"

/**
 * @brief A module which puts the DetectorStatus into the 
 * data stream.  Looks at the I3DetectorStatusOrigin to accomplish this.
 */
class I3DetectorStatusSource : public I3PhysicsModule
{
 public:
  I3DetectorStatusSource(I3Context& context);

  void Process();

  virtual DetectorStatusPair GetDetectorStatus(I3Time time) = 0;

  virtual bool IsDetectorStatusCurrent(I3Time time);

 private:

  I3Boxes& GetBoxes();

  void SendDetectorStatus(I3Time time);
    
  DetectorStatusPair currentDetectorStatus_;

  I3TimeRange currentDetectorStatusRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
