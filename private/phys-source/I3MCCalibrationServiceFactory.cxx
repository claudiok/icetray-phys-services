#include "phys-services/source/I3MCCalibrationServiceFactory.h"
#include "phys-services/source/I3MCCalibrationService.h"
#include "phys-services/I3GeometryService.h"

I3_SERVICE_FACTORY(I3MCCalibrationServiceFactory);

I3MCCalibrationServiceFactory::
I3MCCalibrationServiceFactory(const I3Context& context) : 
  I3ServiceFactory(context){}

I3MCCalibrationServiceFactory::
~I3MCCalibrationServiceFactory(){}

void I3MCCalibrationServiceFactory::Configure(){}

bool I3MCCalibrationServiceFactory::InstallService(I3Context& services)
{
  if(!calibration_){
    calibration_ = 
      shared_ptr<I3MCCalibrationService>
      (new I3MCCalibrationService());
    I3Time t(2006,0);
    log_debug("Attempting to get geometry...");
    context_.dump();
    I3GeometryConstPtr geo = context_.Get<I3GeometryService>().GetGeometry(t);
    log_debug("Successfully got the geometry.");
    if(!geo) log_fatal("Couldn't get geometry.");
    log_debug("Attempting to fill detector status...");
    calibration_->Fill(geo);
    log_debug("Successfully filled the detector status.");
  }
  return services.Put<I3CalibrationService>(calibration_);
}

