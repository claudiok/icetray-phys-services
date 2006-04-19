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
      (new I3MCRawDOMStatusService(context_.Get<I3GeometryServicePtr>()));
    log_debug("Made new I3MCRawDOMStatusService.");
  }

  if(!calibration_){
    calibration_ = 
      shared_ptr<I3MCCalibrationService>
      (new I3MCCalibrationService(context_.Get<I3GeometryServicePtr>()));
    log_debug("Made new I3MCCalibrationService.");
  }


  bool good_calib = services.Put<I3CalibrationService>(calibration_);
  log_debug("good_calib %d",good_calib);
  bool good_status = services.Put<I3DetectorStatusService>(status_);
  log_debug("good_status %d",good_status);

  return (good_calib && good_status);
	  
}

