#ifndef I3DUMMYCALIBORIGIN_H
#define I3DUMMYCALIBORIGIN_H

#include "phys-source/I3CalibrationOrigin.h"
#include <cmath>

/**
 * @brief An implementation of the I3CalibrationOrigin which 
 * just serves up one calibration which is empty.
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3DummyCalibOrigin : public I3CalibrationOrigin
{
 public:
  CalibrationPair GetCalibration(I3Time time)
    {
      CalibrationPair p;
      p.calibration = I3CalibPtr(new I3Calibration());
      p.header = I3CalibrationHeaderPtr(new I3CalibrationHeader());
      return p;
    }
  
  I3TimeRange GetCalibrationValidityRange(I3Time time)
    {
      I3Time lower;
      lower.SetDaqTime(0,0);
      I3Time upper;
      upper.SetDaqTime(3000,0);
      return I3TimeRange(lower,upper);
    }
};

typedef PtrPolicy<I3DummyCalibOrigin>::ThePolicy I3DummyCalibOriginPtr;


#endif
