#include "phys-source/I3FileGeoOriginFactory.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

I3FileGeoOriginFactory::I3FileGeoOriginFactory(const I3Context& context)
  : I3ServiceFactory(context),
    amaGeoFile_("amanda.geo"),
    icecubeGeoFile_("icecube.geo")
{
  AddParameter("AmandaGeoFile",
	       "Geometry file for the AMANDA detector",
	       amaGeoFile_);
  AddParameter("IceCubeGeoFile",
	       "Geometry file for the IceCube detector",
	       icecubeGeoFile_);
}

I3FileGeoOriginFactory::~I3FileGeoOriginFactory()
{
}

void I3FileGeoOriginFactory::Configure()
{
  GetParameter("AmandaGeoFile",amaGeoFile_);
  GetParameter("IceCubeGeoFile",icecubeGeoFile_);
}

bool
I3FileGeoOriginFactory::InstallService(I3Services& services)
{
  if(!origin_)
    origin_ = I3FileGeoOriginPtr(new I3FileGeoOrigin(amaGeoFile_,
							  icecubeGeoFile_));
  return I3ServicesAccess<I3GeometryOrigin>::Put(services,
						 origin_,
						 I3GeometryOrigin::DefaultName());
}
