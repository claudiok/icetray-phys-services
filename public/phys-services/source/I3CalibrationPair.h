#ifndef I3CALIBRATIONPAIR_H
#define I3CALIBRATIONPAIR_H

#include "dataclasses/I3Calibration.h"
#include "dataclasses/I3CalibrationHeader.h"

/**
 * @brief Dumb struct for holding an I3Calibration and its I3CalibrationHeader
 */
struct CalibrationPair
{
  I3CalibrationPtr calibration;
  I3CalibrationHeaderPtr header;

  operator bool()
  {
    if(calibration && header)
      return true;
    return false;
  }
};

#endif
