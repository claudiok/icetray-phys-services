#ifndef I3PSIDUMMYSERVICEFACTORY_H
#define I3PSIDUMMYSERVICEFACTORY_H
/*
 * class: I3PSI_DummyFactory
 *
 * Version $Id: I3PSI_DummyFactory.h,v 1.1 2004/02/20 15:01:31 pretz Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Header files

#ifndef I3TYPES
#include "icetray/I3types"
#endif // I3TYPE

// forward declarations

class I3Context;
class I3Services;
class PSI_Dummy;

// superclasses

#include "icetray/I3ServiceFactory.h"

// namespace declarations

using namespace std;

/**
 * This class installs a I3PSI_DummyFactory.
 *
 * @version $Id: I3PSI_DummyFactory.h,v 1.1 2004/02/20 15:01:31 pretz Exp $
 * @author pretz
 */
class I3PSI_DummyFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3PSI_DummyFactory(const char* name = 0);

  virtual ~I3PSI_DummyFactory();

  // public member functions

  /**
   * Installed this objects service into the specified services object.
   *
   * @param services the I3Services into which the service should be installed.
   * @param context the I3Context in which the service will exist.
   * @param moduleName the name associated with the module whose service is
   * being installed.
   * @return true if the services is successfully installed.
   */
  virtual Bool_t InstallService(I3Services& services,
				const I3Context& context,
				const char* moduleName);

 private:

  // private constructors, destructor and assignment

  I3PSI_DummyFactory
    (const I3PSI_DummyFactory& rhs); // stop default
  I3PSI_DummyFactory operator=
    (const I3PSI_DummyFactory& rhs); // stop default

  // instance member data

  PSI_Dummy* fPhotonics;

  // ROOT macros
  ClassDef(I3PSI_DummyFactory,0);
};

#endif // ROOTI3BOXESFACTORY_H
