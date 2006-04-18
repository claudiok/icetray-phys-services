#include "phys-services/source/I3MCRawDOMStatusServiceFactory.h"
#include "phys-services/source/I3MCRawDOMStatusService.h"
#include "phys-services/I3GeometryService.h"

I3_SERVICE_FACTORY(I3MCRawDOMStatusServiceFactory);

I3MCRawDOMStatusServiceFactory::
I3MCRawDOMStatusServiceFactory(const I3Context& context) : 
  I3ServiceFactory(context){}

I3MCRawDOMStatusServiceFactory::
~I3MCRawDOMStatusServiceFactory(){}

void I3MCRawDOMStatusServiceFactory::Configure(){}

bool I3MCRawDOMStatusServiceFactory::InstallService(I3Context& services)
{
  if(!status_){
    status_ = 
      shared_ptr<I3MCRawDOMStatusService>
      (new I3MCRawDOMStatusService());
    I3Time t(2006,0);
    log_debug("Attempting to get geometry...");
    context_.dump();
    I3GeometryConstPtr geo = context_.Get<I3GeometryService>().GetGeometry(t);
    log_debug("Successfully got the geometry.");
    if(!geo) log_fatal("Couldn't get geometry.");
    log_debug("Attempting to fill detector status...");
    status_->Fill(geo);
    log_debug("Successfully filled the detector status.");
  }
  return services.Put<I3DetectorStatusService>(status_);
}

