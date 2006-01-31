#include "phys-services/source/I3TextFileGeometryServiceFactory.h"
#include "phys-services/source/I3TextFileGeometryService.h"
#include <icetray/I3ServicesAccess.h>

I3_SERVICE_FACTORY(I3TextFileGeometryServiceFactory);

I3TextFileGeometryServiceFactory::
I3TextFileGeometryServiceFactory(const I3Context& context) : 
  I3ServiceFactory(context)
{
  AddParameter("AmandaGeoFile","",amandaFile_);
  AddParameter("IceCubeGeoFile","",icecubeFile_);
}

I3TextFileGeometryServiceFactory::
~I3TextFileGeometryServiceFactory()
{

}

void I3TextFileGeometryServiceFactory::Configure()
{
  GetParameter("AmandaGeoFile",amandaFile_);
  GetParameter("IceCubeGeoFile",icecubeFile_);
}

bool I3TextFileGeometryServiceFactory::InstallService(I3Services& services)
{
  if(!geometry_)
    geometry_ = 
      shared_ptr<I3TextFileGeometryService>
      (new I3TextFileGeometryService(amandaFile_,
				    icecubeFile_));
  return 
    I3ServicesAccess<I3GeometryService>::Put(services,
					     geometry_,
					     I3GeometryService::DefaultName());
}

