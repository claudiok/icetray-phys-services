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
#include "phys-services/source/I3TimeRange.h"
#include "icetray/services/I3Boxes.h"
#include "I3DetectorStatusPair.h"

/**
 * @brief A module which puts the DetectorStatus into the 
 * data stream. 
 *
 * Users are expected to override the 
 * I3DetectorStatusSource::GetDetectorStatus(I3Time time) to get their
 * DetectorStatus data into icetray.
 * 
 * Optionally people writing subclasses of I3DetectorStatusSource can 
 * override the I3DetectorStatusSource::IsDetectorStatusCurrent(I3Time time)
 * method and change the logic that is used when deciding when to 
 * send out a new DetectorStatus.  The default behavior is to use
 * the StartTime and EndTime of the last DetectorStatus sent
 */
class I3DetectorStatusSource : public I3PhysicsModule
{
 public:
  I3DetectorStatusSource(const I3Context& context);

  void Process();

  /**
   * This method should be written to return a newly allocated
   * I3DetectorStatus and I3DetectorStatusHeader for the given
   * time.  The start time and end time of the header should be
   * valid.
   */
  virtual DetectorStatusPair GetDetectorStatus(I3Time time) = 0;

  /**
   * Called internally to check whether the last DetectorStatus sent out
   * is current or not by looking at the StartTime and end time on the
   * last DetectorStatus.  Can be overridden to change this behavior
   */
  virtual bool IsDetectorStatusCurrent(I3Time time);

  SET_LOGGER("I3DetectorStatusSource");
 private:

  I3Boxes& GetBoxes();

  void SendDetectorStatus(I3Time time);
    
  DetectorStatusPair currentDetectorStatus_;

  I3TimeRange currentDetectorStatusRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
