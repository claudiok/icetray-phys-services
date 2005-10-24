#ifndef I3SPRNGRANDOMSERVICEFACTORY_H
#define I3SPRNGRANDOMSERVICEFACTORY_H
/*
 * class: I3SPRNGRandomServiceFactory
 *
 * Date: 04/01/2005

 * @brief This class installs a I3SPRNGRandomService. 
 * Based on I3GSLRandomService by pretz
 *
 * @version $Id$
 * @author juancarlos
 *
 * (c) IceCube Collaboration
 */

// forward declarations

class I3Context;
class I3Services;

// superclasses

#include "icetray/I3ServiceFactory.h"
#include "phys-services/I3RandomService.h"

// namespace declarations

using namespace std;

/**
 * @brief This class installs a I3SPRNGRandomService.
 *
 * I3SPRNGRandomService supports three parameter:
 * <VAR>Seed</VAR>, <VAR>NStreams</VAR>, <VAR>StreamNum</VAR>.
 */
class I3SPRNGRandomServiceFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3SPRNGRandomServiceFactory(const I3Context& context);

  virtual ~I3SPRNGRandomServiceFactory();

  // public member functions

  /**
   * Installed this objects service into the specified services object.
   *
   * @param services the I3Services into which the service should be installed.
   * @return true if the services is successfully installed.
   */
  virtual bool InstallService(I3Services& services);

  /**
   * Configure service prior to installing it. 
   */
  virtual void Configure();

 private:

  // private constructors, destructor and assignment

  I3SPRNGRandomServiceFactory
    (const I3SPRNGRandomServiceFactory& rhs); // stop default
  I3SPRNGRandomServiceFactory operator=
    (const I3SPRNGRandomServiceFactory& rhs); // stop default

  // instance member data
  int seed_, nstreams_, streamnum_;
  string instatefile_,outstatefile_;
  I3RandomServicePtr random_;

  SET_LOGGER("I3SPRNGRandomServiceFactory");
  
};

#endif
