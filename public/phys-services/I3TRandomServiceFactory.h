#ifndef I3TRANDOMSERVICEFACTORY_H
#define I3TRANDOMSERVICEFACTORY_H
/*
 * class: I3TRandomServiceFactory
 *
 * Version $Id: I3TRandomServiceFactory.h,v 1.2 2004/03/16 19:20:30 pretz Exp $
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
 * This class installs a I3TRandomService.
 *
 * @version $Id: I3TRandomServiceFactory.h,v 1.2 2004/03/16 19:20:30 pretz Exp $
 * @author pretz
 */
class I3TRandomServiceFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3TRandomServiceFactory(const char* name = 0);

  virtual ~I3TRandomServiceFactory();

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

  I3TRandomServiceFactory
    (const I3TRandomServiceFactory& rhs); // stop default
  I3TRandomServiceFactory operator=
    (const I3TRandomServiceFactory& rhs); // stop default

  // instance member data

  // ROOT macros
  ClassDef(I3TRandomServiceFactory,0);
};

#endif // ROOTI3BOXESFACTORY_H
