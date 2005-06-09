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
#include "phys-source/I3TimeRange.h"

/**
 * @brief Dumb struct for holding an I3Calibration and its I3CalibrationHeader
 */
struct CalibrationPair
{
  I3CalibPtr calibration;
  I3CalibrationHeaderPtr header;

  operator bool()
  {
    if(calibration && header)
      return true;
    return false;
  }
};

/**
 * @brief A module which fills the Calibration into the data stream
 * when it becomes outdated.
 *
 */
class I3CalibrationSource : public I3PhysicsModule
{
 public:
  I3CalibrationSource(I3Context& context);

  void Physics(I3Frame& frame);
  
  void Calibration(I3Frame& frame);

  /**
   * virtual, but should only be implemented if you want to change
   * the logic for when the geometry is updated
   */
  virtual bool ShouldUpdateCalibration(I3Frame& frame);

  /**
   * Give me the geometry that should be in this frame
   */
  virtual CalibrationPair GetCalibration(I3Frame& frame,I3Time eventTime) = 0;

 private:
  void CurrentCalibrationIntoFrame(I3Frame& frame);

  CalibrationPair currentCalibration_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
