#ifndef I3STDCALCULATORFACTORY_H
#define I3STDCALCULATORFACTORY_H
/*
 * class: I3StdCalculatorFactory
 *
 * Version $Id: I3StdCalculatorFactory.h,v 1.1 2004/06/24 14:27:55 pretz Exp $
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
class I3Calculator;

// superclasses

#include "icetray/I3ServiceFactory.h"

// namespace declarations

using namespace std;

/**
 * This class installs a I3StdCalculatorFactory.
 *
 * @version $Id: I3StdCalculatorFactory.h,v 1.1 2004/06/24 14:27:55 pretz Exp $
 * @author pretz
 */
class I3StdCalculatorFactory
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3StdCalculatorFactory(const char* name = 0);

  virtual ~I3StdCalculatorFactory();

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

  I3StdCalculatorFactory
    (const I3StdCalculatorFactory& rhs); // stop default
  I3StdCalculatorFactory operator=
    (const I3StdCalculatorFactory& rhs); // stop default

  // instance member data

  I3Calculator* fCalculator;

  // ROOT macros
  ClassDef(I3StdCalculatorFactory,0);
};

#endif // ROOTI3BOXESFACTORY_H
