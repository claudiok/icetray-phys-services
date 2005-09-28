#include "phys-services/I3FileOMKey2MBIDFactory.h"
#include "phys-services/I3FileOMKey2MBID.h"

#include "icetray/I3ServicesAccess.h"

#include "phys-services/I3TRandomService.h"

I3_SERVICE_FACTORY(I3FileOMKey2MBIDFactory);

I3FileOMKey2MBIDFactory::I3FileOMKey2MBIDFactory(const I3Context& context)
  : I3ServiceFactory(context)
{
  AddParameter("Infile",
	       "The file to read the OMKey to MBID conversions",
	       infile_);
}

bool
I3FileOMKey2MBIDFactory::InstallService(I3Services& services)
{
  if(!service_)
    service_ = I3OMKey2MBIDPtr ( new I3FileOMKey2MBID(infile_));
  return I3ServicesAccess<I3OMKey2MBID>::Put(services,
					     service_,
					     I3OMKey2MBID::DefaultName());
}

void I3FileOMKey2MBIDFactory::Configure()
{
  GetParameter("Infile",infile_);
}
