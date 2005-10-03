#ifndef I3PARTICEDATASERVICEFACTORY_H
#define I3PARTICEDATASERVICEFACTORY_H
/*
 * class: I3ParticleDataServiceFactory
 *
 * Version $Id$
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Header files


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
 * @version $Id$
 * @author pretz
 */
class I3ParticleDataServiceFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3ParticleDataServiceFactory(const I3Context& context);

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
  virtual bool InstallService(I3Services& services);

 private:

  // private constructors, destructor and assignment

  I3ParticleDataServiceFactory
    (const I3ParticleDataServiceFactory& rhs); // stop default
  I3ParticleDataServiceFactory operator=
    (const I3ParticleDataServiceFactory& rhs); // stop default

  // instance member data

};


#endif // ROOTI3BOXESFACTORY_H
