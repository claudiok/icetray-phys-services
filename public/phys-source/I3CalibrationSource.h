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
 * Uses the I3CalibrationOrigin service to do this.
 * Also fills the calibration in all faster streams
 */
class I3CalibrationSource : public I3PhysicsModule
{
 public:
  I3CalibrationSource(I3Context& context);

  void Process();

  virtual CalibrationPair GetCalibration(I3Time time) = 0;

  virtual bool IsCalibrationCurrent(I3Time time);

 private:
  I3Boxes& GetBoxes();

  void SendCalibration(I3Time time);
  
  CalibrationPair currentCalibration_;
  I3TimeRange currentCalibrationRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
