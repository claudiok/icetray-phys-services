#include "phys-source/I3DummyEventOriginFactory.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

I3DummyEventOriginFactory::I3DummyEventOriginFactory(const I3Context& context)
  : I3ServiceFactory(context)
{
}

I3DummyEventOriginFactory::~I3DummyEventOriginFactory()
{
}

bool
I3DummyEventOriginFactory::InstallService(I3Services& services)
{
  if(!eventOrigin_)
    eventOrigin_ = I3DummyEventOriginPtr(new I3DummyEventOrigin());
  return I3ServicesAccess<I3EventOrigin>::Put(services,
						eventOrigin_,
						I3EventOrigin::DefaultName());
}
