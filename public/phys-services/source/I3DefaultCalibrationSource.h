#ifndef I3DEFAULTCALIBRATIONSOURCE_H
#define I3DEFAULTCALIBRATIONSOURCE_H

#include "I3CalibrationSource.h"

class I3DefaultCalibrationSource : public I3CalibrationSource
{
 public:
  I3DefaultCalibrationSource(const I3Context& context);

  CalibrationPair GetCalibration(I3Time eventTime);


};


#endif
