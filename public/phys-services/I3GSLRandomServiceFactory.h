#ifndef I3GSLRANDOMSERVICEFACTORY_H
#define I3GSLRANDOMSERVICEFACTORY_H
/*
 * class: I3GSLRandomServiceFactory
 *
 * Version $Id: I3GSLRandomServiceFactory.h,v 1.2 2004/10/20 12:12:15 pretz Exp $
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
#include "phys-services/I3GSLRandomService.h"

// namespace declarations

using namespace std;

/**
 * @brief This class installs a I3GSLRandomService.
 *
 * @version $Id: I3GSLRandomServiceFactory.h,v 1.2 2004/10/20 12:12:15 pretz Exp $
 * @author pretz
 */
class I3GSLRandomServiceFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3GSLRandomServiceFactory(I3Context& context);

  virtual ~I3GSLRandomServiceFactory();

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
  virtual Bool_t InstallService(I3Services& services);

 private:

  // private constructors, destructor and assignment

  I3GSLRandomServiceFactory
    (const I3GSLRandomServiceFactory& rhs); // stop default
  I3GSLRandomServiceFactory operator=
    (const I3GSLRandomServiceFactory& rhs); // stop default

  // instance member data
  I3RandomServicePtr random;
  
  // ROOT macros
  ClassDef(I3GSLRandomServiceFactory,0);
};

#endif
