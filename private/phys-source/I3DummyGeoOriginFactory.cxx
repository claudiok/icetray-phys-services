#include "phys-source/I3DummyGeoOriginFactory.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

I3DummyGeoOriginFactory::I3DummyGeoOriginFactory(const I3Context& context)
  : I3ServiceFactory(context)
{
}

I3DummyGeoOriginFactory::~I3DummyGeoOriginFactory()
{
}

Bool_t
I3DummyGeoOriginFactory::InstallService(I3Services& services)
{
  if(!eventOrigin_)
    eventOrigin_ = I3DummyGeoOriginPtr(new I3DummyGeoOrigin());
  return I3ServicesAccess<I3GeometryOrigin>::Put(services,
						eventOrigin_,
						I3GeometryOrigin::DefaultName());
}
