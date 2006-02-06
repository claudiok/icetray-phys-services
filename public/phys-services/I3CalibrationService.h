/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3CalibrationService.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3CALIBRATIONSERVICE_H
#define I3CALIBRATIONSERVICE_H

#include "phys-services/I3TimeRange.h"
#include "dataclasses/calibration/I3Calibration.h"
#include "dataclasses/Utility.h"

/**
 * @brief Produces I3Calibration objects given a time.
 * Then it tells the next time the calibration will change.
 */
class I3CalibrationService
{
 public:
  /**
   * @brief default name for the service in the icetray context.
   */
  static const char* DefaultName() { return "CalibrationService";}

  /**
   * @brief Gets the calibration and the header associated with the given time
   * It is expected that the 'start' and 'end' times of the data
   * header will be appropirately filled.
   */
  virtual I3CalibrationPtr GetCalibration(I3Time time) = 0;
};

typedef shared_ptr<I3CalibrationService> I3CalibrationServicePtr;

#endif
