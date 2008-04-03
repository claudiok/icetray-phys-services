#ifndef I3CALIBRATIONPAIR_H
#define I3CALIBRATIONPAIR_H

#include "dataclasses/calibration/I3Calibration.h"

/**
 * @brief Dumb struct for holding an I3Calibration and its I3CalibrationHeader
 */
struct CalibrationPair
{
  I3CalibrationPtr calibration;

  operator bool()
  {
    if(calibration)
      return true;
    return false;
  }
};

#endif
