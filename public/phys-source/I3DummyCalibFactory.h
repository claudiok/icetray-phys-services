#ifndef I3DUMMYCALIBFACTORY_H
#define I3DUMMYCALIBFACTORY_H

#include "phys-source/I3CalibrationFactory.h"
#include <cmath>

/**
 * @brief An implementation of the I3CalibrationFactory which 
 * just serves up one calibration which is empty.
 *
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
class I3DummyCalibFactory : public I3CalibrationFactory
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

  I3DummyCalibFactory() : nextTime_(-INFINITY){}
};

typedef PtrPolicy<I3DummyCalibFactory>::ThePolicy I3DummyCalibFactoryPtr;


#endif
