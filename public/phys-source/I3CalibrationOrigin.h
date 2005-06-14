/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3CalibrationOrigin.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3CALIBRATIONORIGIN_H
#define I3CALIBRATIONORIGIN_H

#include "I3TimeRange.h"
#include "dataclasses/I3Calibration.h"
#include "dataclasses/I3CalibrationHeader.h"
#include "dataclasses/StoragePolicy.h"
#include "I3CalibrationPair.h"

/**
 * @brief Produces I3Calibration objects given a time.
 * Then it tells the next time the calibration will change.
 */
class I3CalibrationOrigin
{
 public:
  /**
   * @brief default name for the service in the icetray context.
   */
  static const char* DefaultName() { return "CalibrationOrigin";}

  /**
   * @brief Gets the calibration and the header associated with the given time
   * It is expected that the 'start' and 'end' times of the data
   * header will be appropirately filled.
   */
  virtual CalibrationPair GetCalibration(I3Time time) = 0;
};

typedef shared_ptr<I3CalibrationOrigin> I3CalibrationOriginPtr;

#endif
