#include "phys-services/source/I3MCSourceServiceFactory.h"
#include "phys-services/source/I3MCRawDOMStatusService.h"
#include "phys-services/source/I3MCCalibrationService.h"
#include "dataclasses/physics/I3Trigger.h"
#include "dataclasses/status/I3TriggerStatus.h"

I3_SERVICE_FACTORY(I3MCSourceServiceFactory);

I3MCSourceServiceFactory::
I3MCSourceServiceFactory(const I3Context& context) : 
  I3ServiceFactory(context),
  configID_(0),
  threshold_(16),
  timeWindow_(7000)
{
  AddParameter("Threshold","Multiplicity Trigger Threshold",threshold_);
  AddParameter("TimeWindow","Multiplicity Trigger Time Window",timeWindow_);
  AddParameter("ConfigID","Trigger Status Config ID",configID_);
}

I3MCSourceServiceFactory::
~I3MCSourceServiceFactory(){}

void I3MCSourceServiceFactory::Configure()
{
  GetParameter("Threshold",threshold_);
  GetParameter("TimeWindow",timeWindow_);
  GetParameter("ConfigID",configID_);

  Trigger.GetTriggerKey() = TriggerKey(TriggerKey::IN_ICE, TriggerKey::SIMPLE_MULTIPLICITY, configID_);

  TrigStatus.GetTriggerName().append("simple_multiplicity");
  TrigStatus.GetTriggerSettings().insert(make_pair("threshold", threshold_));
  TrigStatus.GetTriggerSettings().insert(make_pair("timeWindow", timeWindow_));
}

bool I3MCSourceServiceFactory::InstallService(I3Context& services)
{

  if(!status_){
    status_ = 
      shared_ptr<I3MCRawDOMStatusService>
      (new I3MCRawDOMStatusService(context_.Get<I3GeometryServicePtr>()));
    log_debug("Made new I3MCRawDOMStatusService.");

    status_->SetTriggerStatus(Trigger, TrigStatus);
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

