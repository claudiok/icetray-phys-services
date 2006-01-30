#ifndef I3EMPTYDETECTORSTATUSSERVICE_H
#define I3EMPTYDETECTORSTATUSSERVICE_H

#include "phys-services/I3DetectorStatusService.h"

class I3EmptyDetectorStatusService : public I3DetectorStatusService
{
 public:
  I3EmptyDetectorStatusService();
  
  DetectorStatusPair GetDetectorStatus(I3Time time);

 private:

  DetectorStatusPair pair_;
};

#endif
