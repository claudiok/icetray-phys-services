#include "phys-source/I3DummyEventOriginFactory.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

I3DummyEventOriginFactory::I3DummyEventOriginFactory(const I3Context& context)
  : I3ServiceFactory(context),
    maxEvents_(10)
{
  AddParameter("EventsToReturn",
	       "The maximum number of events to return",
	       maxEvents_);
}

I3DummyEventOriginFactory::~I3DummyEventOriginFactory()
{
}

void I3DummyEventOriginFactory::Configure()
{
  GetParameter("EventsToReturn",maxEvents_);
}

bool
I3DummyEventOriginFactory::InstallService(I3Services& services)
{
  if(!eventOrigin_)
    eventOrigin_ = I3DummyEventOriginPtr(new I3DummyEventOrigin(maxEvents_));
  return I3ServicesAccess<I3EventOrigin>::Put(services,
						eventOrigin_,
						I3EventOrigin::DefaultName());
}