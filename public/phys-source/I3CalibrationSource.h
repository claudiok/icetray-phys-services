#ifndef I3CALIBRATIONSOURCE_H
#define I3CALIBRATIONSOURCE_H

#include "phys-services/I3PhysicsModule.h"
#include "phys-source/I3CalibrationOrigin.h"
#include "phys-source/I3TimeRange.h"

class I3CalibrationSource : public I3PhysicsModule
{
 public:
  I3CalibrationSource(I3Context& context);

  void Physics(I3Frame& frame);
  
  void Calibration(I3Frame& frame);

 private:
  void SendCalibration(I3Time time);
  
  bool IsCalibrationCurrent(I3Time time);
  
  I3CalibrationOrigin& GetCalibrationFactory();
  
  CalibrationPair currentCalibration_;
  I3TimeRange currentCalibrationRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
