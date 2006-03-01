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
  cout<<"entering "<<__PRETTY_FUNCTION__<<endl;
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
  cout<<"exiting "<<__PRETTY_FUNCTION__<<endl;
}

void I3EmptyStreamsFactory::Configure()
{
  cout<<"entering "<<__PRETTY_FUNCTION__<<endl;
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
  cout<<"exiting "<<__PRETTY_FUNCTION__<<endl;
}

bool I3EmptyStreamsFactory::InstallService(I3Context& services)
{
  bool success = true;

  if(installEvents_)
    success *= 
      services.Put<I3EventService>(events_);

  if(installCalibrations_)
    success *=
      services.Put<I3CalibrationService>(calibrations_);

  if(installStatus_)
    success *= 
      services.Put<I3DetectorStatusService>(status_);

  if(installGeometries_)
    success *= 
      services.Put<I3GeometryService>(geometries_);

  return success;

}
