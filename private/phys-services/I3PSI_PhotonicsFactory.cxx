/*
 * class: I3PSI_PhotonicsFactory
 *
 * Version $Id: I3PSI_PhotonicsFactory.cxx,v 1.3 2004/03/04 19:04:34 pretz Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Class header files

#include "phys-services/I3PSI_PhotonicsFactory.h"

ClassImp(I3PSI_PhotonicsFactory);

// Other header files

#include "icetray/I3ServicesAccess.h"

#include "PSI_Photonics.h"
#include "PSInterface.h"
#include <cstdlib>

// Constructors

I3PSI_PhotonicsFactory::I3PSI_PhotonicsFactory(const char* name)
  : I3ServiceFactory(name),
    fPhotonics(0)
{
  if (0 == GetServiceName()) {
    SetServiceName("PSInterface");
  }
}

// Destructors

I3PSI_PhotonicsFactory::~I3PSI_PhotonicsFactory()
{
}

// Member functions

Bool_t
I3PSI_PhotonicsFactory::InstallService(I3Services& services,
				   const I3Context& context,
				   const char* moduleName)
{
  if(!fPhotonics){
    fPhotonics = new PSI_Photonics();
    if(!fPhotonics->LoadTables(0,"level1_table.list","level2_table.list",0)){
      cout<<"loading photonics tables failed.  Aborting"<<endl;
      exit(1);
    }
  }
  return I3ServicesAccess<PSInterface>::Put(services,
					    fPhotonics,
					    GetServiceName());
}
