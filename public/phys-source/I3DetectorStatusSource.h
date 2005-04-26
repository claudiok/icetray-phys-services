#ifndef I3DETECTORSTATUSSOURCE_H
#define I3DETECTORSTATUSSOURCE_H

#include "phys-services/I3PhysicsModule.h"
#include "phys-source/I3DetectorStatusOrigin.h"
#include "phys-source/I3TimeRange.h"

class I3DetectorStatusSource : public I3PhysicsModule
{
 public:
  I3DetectorStatusSource(I3Context& context);

  void Physics(I3Frame& frame);
  
  void DetectorStatus(I3Frame& frame);

 private:
  void SendDetectorStatus(I3Time time);
  
  bool IsDetectorStatusCurrent(I3Time time);
  
  I3DetectorStatusOrigin& GetDetectorStatusFactory();
  
  DetectorStatusPair currentDetectorStatus_;
  I3TimeRange currentDetectorStatusRange_;

  I3Frame& CreateFrame(const I3Stream& stop);
};

#endif
