#include "phys-source/I3DummyCalibOriginFactory.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

I3DummyCalibOriginFactory::I3DummyCalibOriginFactory(const I3Context& context)
  : I3ServiceFactory(context)
{
}

I3DummyCalibOriginFactory::~I3DummyCalibOriginFactory()
{
}

Bool_t
I3DummyCalibOriginFactory::InstallService(I3Services& services)
{
  if(!eventOrigin_)
    eventOrigin_ = I3DummyCalibOriginPtr(new I3DummyCalibOrigin());
  return I3ServicesAccess<I3CalibrationOrigin>
    ::Put(services,
	eventOrigin_,
	I3CalibrationOrigin::DefaultName());
}
