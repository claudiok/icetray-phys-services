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
  double nextTime_;
 public:
  CalibrationPair GetCalibration(Time time)
    {
      CalibrationPair p;
      p.calibration = I3CalibPtr(new I3Calibration());
      p.header = I3CalibrationHeaderPtr(new I3CalibrationHeader());
      nextTime_ = INFINITY;
      return p;
    }
  
  Time NextCalibrationTime()
    {
      return nextTime_;
    }

  I3DummyCalibOrigin() : nextTime_(-INFINITY){}
};

typedef PtrPolicy<I3DummyCalibOrigin>::ThePolicy I3DummyCalibOriginPtr;


#endif
