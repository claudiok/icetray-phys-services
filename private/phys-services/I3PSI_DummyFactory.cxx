/*
 * class: I3PSI_DummyFactory
 *
 * Version $Id: I3PSI_DummyFactory.cxx,v 1.1 2004/02/20 15:01:27 pretz Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3PSI_DummyFactory.h"

ClassImp(I3PSI_DummyFactory);

// Other header files

#include "icetray/I3ServicesAccess.h"

#include "PSI_Dummy.h"
#include "PSInterface.h"

// Constructors

I3PSI_DummyFactory::I3PSI_DummyFactory(const char* name)
  : I3ServiceFactory(name),
    fPhotonics(0)
{
  if (0 == GetServiceName()) {
    SetServiceName("PSInterface");
  }
}

// Destructors

I3PSI_DummyFactory::~I3PSI_DummyFactory()
{
}

// Member functions

Bool_t
I3PSI_DummyFactory::InstallService(I3Services& services,
				   const I3Context& context,
				   const char* moduleName)
{
  if(!fPhotonics)
    fPhotonics = new PSI_Dummy();
  return I3ServicesAccess<PSInterface>::Put(services,
					    fPhotonics,
					    GetServiceName());
}
