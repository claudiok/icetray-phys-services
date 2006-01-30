#ifndef I3EMPTYCALIBRATIONSERVICE_H
#define I3EMPTYCALIBRATIONSERVICE_H

#include "phys-services/I3CalibrationService.h"

class I3EmptyCalibrationService : public I3CalibrationService
{
 public:
  I3EmptyCalibrationService();
  
  CalibrationPair GetCalibration(I3Time time);

 private:

  CalibrationPair pair_;
};

#endif
