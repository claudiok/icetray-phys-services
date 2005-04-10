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
  CalibrationPair GetCalibration(I3Time time);
};

typedef PtrPolicy<I3DummyCalibOrigin>::ThePolicy I3DummyCalibOriginPtr;


#endif
