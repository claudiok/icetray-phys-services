#ifndef I3CALIBRATIONPAIR_H
#define I3CALIBRATIONPAIR_H

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

#endif
