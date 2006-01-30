#include "phys-services/empty-streams/I3EmptyStreamsFactory.h"

#include "phys-services/empty-streams/I3EmptyEventService.h"
#include "phys-services/empty-streams/I3EmptyGeometryService.h"
#include "phys-services/empty-streams/I3EmptyDetectorStatusService.h"
#include "phys-services/empty-streams/I3EmptyCalibrationService.h"
#include <icetray/I3ServicesAccess.h>

I3_SERVICE_FACTORY(I3EmptyStreamsFactory);

I3EmptyStreamsFactory::I3EmptyStreamsFactory(const I3Context& context) : 
  I3ServiceFactory(context), nframes_(10)
{
  AddParameter("NFrames","Number of event frames to spit out",nframes_);
}

void I3EmptyStreamsFactory::Configure()
{
  GetParameter("NFrames",nframes_);

  events_ = 
    shared_ptr<I3EventService>(new I3EmptyEventService(nframes_));
  calibrations_ = 
    shared_ptr<I3CalibrationService>(new I3EmptyCalibrationService());
  status_ = 
    shared_ptr<I3DetectorStatusService>(new I3EmptyDetectorStatusService());
  geometries_ = 
    shared_ptr<I3GeometryService>(new I3EmptyGeometryService());
}

bool I3EmptyStreamsFactory::InstallService(I3Services& services)
{
  bool success = true;

  success *= 
    I3ServicesAccess<I3EventService>::Put(services,
					  events_,
					  I3EventService::DefaultName());
  success *=
    I3ServicesAccess<I3CalibrationService>::Put(services,
						calibrations_,
						I3CalibrationService::DefaultName());

  success *= 
    I3ServicesAccess<I3DetectorStatusService>::Put(services,
						status_,
						I3DetectorStatusService::DefaultName());

  success *= 
    I3ServicesAccess<I3GeometryService>::Put(services,
					     geometries_,
					     I3GeometryService::DefaultName());


  return success;

}
