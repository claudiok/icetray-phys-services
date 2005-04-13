#ifndef I3SPRNGRANDOMSERVICEFACTORY_H
#define I3SPRNGRANDOMSERVICEFACTORY_H
/*
 * class: I3SPRNGRandomServiceFactory
 *
 * Date: 04/01/2005

 * @brief This class installs a I3SPRNGRandomService. 
 * Based on I3GSLRandomService by pretz
 *
 * @version $Id: I3SPRNGRandomServiceFactory.h,v 1.1 2005/04/13 16:29:34 juancarlos Exp $
 * @author juancarlos
 *
 * (c) IceCube Collaboration
 */

// forward declarations

class I3Context;
class I3Services;

// superclasses

#include "icetray/I3ServiceFactory.h"
#include "phys-services/I3SPRNGRandomService.h"

// namespace declarations

using namespace std;

class I3SPRNGRandomServiceFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3SPRNGRandomServiceFactory(I3Context& context);

  virtual ~I3SPRNGRandomServiceFactory();

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

  /**
   * Configure service prior to installing it. 
   */
  virtual void Configure();

 private:

  Int_t seed, nstreams, streamnum;

  // private constructors, destructor and assignment

  I3SPRNGRandomServiceFactory
    (const I3SPRNGRandomServiceFactory& rhs); // stop default
  I3SPRNGRandomServiceFactory operator=
    (const I3SPRNGRandomServiceFactory& rhs); // stop default

  // instance member data
  I3RandomServicePtr random;
  
  // ROOT macros
  ClassDef(I3SPRNGRandomServiceFactory,0);
};

#endif
