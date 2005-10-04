/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3CalibrationSource.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3CALIBRATIONSOURCE_H
#define I3CALIBRATIONSOURCE_H

#include "phys-services/I3PhysicsModule.h"
#include "I3TimeRange.h"
#include "I3CalibrationPair.h"
#include "services/I3Boxes.h"

/**
 * @brief An icetray module which fills the
 * calibration into the data stream when it becomes outdated.
 *
 * Users are expected to override the 
 * I3CalibrationSource::GetCalibration(I3Time time) to get their
 * Calibration data into icetray.
 * 
 * Optionally people writing subclasses of I3CalibrationSource can 
 * override the I3CalibrationSource::IsCalibrationCurrent(I3Time time)
 * method and change the logic that is used when deciding when to 
 * send out a new Calibration.  The default behavior is to use
 * the StartTime and EndTime of the last Calibration sent
 */
class I3CalibrationSource : public I3PhysicsModule
{
 public:
  I3CalibrationSource(const I3Context& context);

  void Process();

  /**
   * This method should be written to return a newly allocated
   * I3Calibration and I3CalibrationHeader for the given
   * time.  The start time and end time of the header should be
   * valid.
   */
  virtual CalibrationPair GetCalibration(I3Time time) = 0;

  /**
   * Called internally to check whether the last Calibration sent out
   * is current or not by looking at the StartTime and end time on the
   * last Calibration.  Can be overridden to change this behavior
   */
  virtual bool IsCalibrationCurrent(I3Time time);

 private:
  I3Boxes& GetBoxes();


  void SendCalibration(I3Time time);
  
  CalibrationPair currentCalibration_;
  I3TimeRange currentCalibrationRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
