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
 * @brief A module which puts the DetectorStatus into the 
 * data stream.  Looks at the I3DetectorStatusOrigin to accomplish this.
 */
class I3DetectorStatusSource : public I3PhysicsModule
{
 public:
  I3DetectorStatusSource(I3Context& context);

  void Physics(I3Frame& frame);
  
  void DetectorStatus(I3Frame& frame);

  virtual DetectorStatusPair GetDetectorStatus(I3Time time) = 0;

 private:
  void SendDetectorStatus(I3Time time);
  
  bool IsDetectorStatusCurrent(I3Time time);
  
  DetectorStatusPair currentDetectorStatus_;
  I3TimeRange currentDetectorStatusRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
