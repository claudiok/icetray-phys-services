#ifndef I3DUMMYCALIBRATIONSOURCE_H
#define I3DUMMYCALIBRATIONSOURCE_H

#include "I3CalibrationSource.h"

class I3DummyCalibrationSource : public I3CalibrationSource
{
 public:
  I3DummyCalibrationSource(const I3Context& context);

  CalibrationPair GetCalibration(I3Time eventTime);


};


#endif
