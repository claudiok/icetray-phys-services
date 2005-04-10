#ifndef I3CALIBRATIONORIGIN_H
#define I3CALIBRATIONORIGIN_H

#include "I3TimeRange.h"
#include "dataclasses/I3Calibration.h"
#include "dataclasses/I3CalibrationHeader.h"
#include "dataclasses/StoragePolicy.h"

/**
 * @brief Dumb struct for holding an I3Calibration and its I3CalibrationHeader
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
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
 * @brief Produces I3Calibration objects given a time.
 * Then it tells the next time the calibration will change.
 * 
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3CalibrationOrigin
{
 public:
  static const char* DefaultName() { return "CalibrationOrigin";}
  virtual CalibrationPair GetCalibration(I3Time time) = 0;
};

typedef PtrPolicy<I3CalibrationOrigin>::ThePolicy I3CalibrationOriginPtr;

#endif
