#ifndef I3PARTICEDATASERVICEFACTORY_H
#define I3PARTICEDATASERVICEFACTORY_H
/*
 * class: I3ParticleDataServiceFactory
 *
 * Version $Id: I3ParticleDataServiceFactory.h,v 1.3 2004/05/10 15:57:54 pretz Exp $
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

// superclasses

#include "icetray/I3ServiceFactory.h"

// namespace declarations

using namespace std;

/**
 * @brief Installs a I3ParticleDataService.
 *
 * @version $Id: I3ParticleDataServiceFactory.h,v 1.3 2004/05/10 15:57:54 pretz Exp $
 * @author pretz
 */
class I3ParticleDataServiceFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3ParticleDataServiceFactory(const char* name = 0);

  virtual ~I3ParticleDataServiceFactory();

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

  I3ParticleDataServiceFactory
    (const I3ParticleDataServiceFactory& rhs); // stop default
  I3ParticleDataServiceFactory operator=
    (const I3ParticleDataServiceFactory& rhs); // stop default

  // instance member data

  // ROOT macros
  ClassDef(I3ParticleDataServiceFactory,0);
};

#endif // ROOTI3BOXESFACTORY_H
