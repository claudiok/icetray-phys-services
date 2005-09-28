#ifndef I3TRANDOMSERVICEFACTORY_H
#define I3TRANDOMSERVICEFACTORY_H
/*
 * class: I3TRandomServiceFactory
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
#include "phys-services/I3RandomService.h"

// namespace declarations

using namespace std;

/**
 * @brief This class installs a I3TRandomService.
 *
 * I3TRandomService supports one parameter: <VAR>Seed</VAR>.
 * @version $Id$
 * @author pretz
 */
class I3TRandomServiceFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3TRandomServiceFactory(const I3Context& context);

  virtual ~I3TRandomServiceFactory();

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

  I3TRandomServiceFactory
    (const I3TRandomServiceFactory& rhs); // stop default
  I3TRandomServiceFactory operator=
    (const I3TRandomServiceFactory& rhs); // stop default

  // instance member data

	int seed_;
	I3RandomServicePtr random_;

};

#endif // ROOTI3BOXESFACTORY_H
