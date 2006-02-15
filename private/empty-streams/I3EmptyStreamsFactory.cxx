#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"

#include "phys-services/empty-streams/I3EmptyEventService.h"
#include "phys-services/empty-streams/I3EmptyGeometryService.h"
#include "phys-services/empty-streams/I3EmptyDetectorStatusService.h"
#include "phys-services/empty-streams/I3EmptyCalibrationService.h"

I3_SERVICE_FACTORY(I3EmptyStreamsFactory);

I3EmptyStreamsFactory::I3EmptyStreamsFactory(const I3Context& context) : 
  I3ServiceFactory(context), 
  nframes_(10),
  installEvents_(true),
  installCalibrations_(true),
  installStatus_(true),
  installGeometries_(true)
{
  AddParameter("NFrames","Number of event frames to spit out",nframes_);
  AddParameter("InstallEvent",
	       "Whether or not to install the Event Service",
	       installEvents_);
  AddParameter("InstallCalibration",
	       "Whether or not to install the Calibration Service",
	       installCalibrations_);
  AddParameter("InstallGeometry",
	       "Whether or not to install the Geometry Service",
	       installGeometries_);
  AddParameter("InstallStatus",
	       "Whether or not to install the DetectorStatus Service",
	       installStatus_);
}

void I3EmptyStreamsFactory::Configure()
{
  GetParameter("NFrames",nframes_);

  GetParameter("InstallEvent",
	       installEvents_);
  GetParameter("InstallCalibration",
	       installCalibrations_);
  GetParameter("InstallGeometry",
	       installGeometries_);
  GetParameter("InstallStatus",
	       installStatus_);

  if(installEvents_)
    events_ = 
      shared_ptr<I3EventService>(new I3EmptyEventService(nframes_));
  if(installCalibrations_)
    calibrations_ = 
      shared_ptr<I3CalibrationService>(new I3EmptyCalibrationService());
  if(installStatus_)
    status_ = 
      shared_ptr<I3DetectorStatusService>(new I3EmptyDetectorStatusService());
  if(installGeometries_)
    geometries_ = 
      shared_ptr<I3GeometryService>(new I3EmptyGeometryService());
}

bool I3EmptyStreamsFactory::InstallService(I3Context& services)
{
  bool success = true;

  if(installEvents_)
    success *= 
      I3ContextAccess<I3EventService>::Put(services,
					    events_,
					    I3EventService::DefaultName());

  if(installCalibrations_)
    success *=
      I3ContextAccess<I3CalibrationService>::Put(services,
						  calibrations_,
						  I3CalibrationService::DefaultName());

  if(installStatus_)
    success *= 
      I3ContextAccess<I3DetectorStatusService>::Put(services,
						     status_,
						     I3DetectorStatusService::DefaultName());

  if(installGeometries_)
    success *= 
      I3ContextAccess<I3GeometryService>::Put(services,
					       geometries_,
					       I3GeometryService::DefaultName());


  return success;

}
