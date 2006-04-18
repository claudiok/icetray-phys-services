#include "phys-services/source/I3MCSourceServiceFactory.h"
#include "phys-services/source/I3MCRawDOMStatusService.h"
#include "phys-services/source/I3MCCalibrationService.h"

I3_SERVICE_FACTORY(I3MCSourceServiceFactory);

I3MCSourceServiceFactory::
I3MCSourceServiceFactory(const I3Context& context) : 
  I3ServiceFactory(context){}

I3MCSourceServiceFactory::
~I3MCSourceServiceFactory(){}

void I3MCSourceServiceFactory::Configure(){}

bool I3MCSourceServiceFactory::InstallService(I3Context& services)
{
  if(!status_){
    status_ = 
      shared_ptr<I3MCRawDOMStatusService>
      (new I3MCRawDOMStatusService());
  }
  return services.Put<I3DetectorStatusService>(status_);

  if(!calibration_){
    calibration_ = 
      shared_ptr<I3MCCalibrationService>
      (new I3MCCalibrationService());
  }
  return services.Put<I3CalibrationService>(calibration_);

}

