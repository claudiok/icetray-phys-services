#ifndef I3CALCULATORFACTORYIMPL_H
#define I3CALCULATORFACTORYIMPL_H
/*
 * class: I3CalculatorFactoryImpl
 *
 * Version $Id: I3CalculatorFactoryImpl.h,v 1.1 2004/06/24 15:04:54 dule Exp $
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
 * This class installs a I3CalculatorFactoryImpl.
 *
 * @version $Id: I3CalculatorFactoryImpl.h,v 1.1 2004/06/24 15:04:54 dule Exp $
 * @author pretz
 */
class I3CalculatorFactoryImpl
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3CalculatorFactoryImpl(const char* name = 0);

  virtual ~I3CalculatorFactoryImpl();

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

  I3CalculatorFactoryImpl
    (const I3CalculatorFactoryImpl& rhs); // stop default
  I3CalculatorFactoryImpl operator=
    (const I3CalculatorFactoryImpl& rhs); // stop default

  // instance member data

  I3Calculator* fCalculator;

  // ROOT macros
  ClassDef(I3CalculatorFactoryImpl,0);
};

#endif // ROOTI3BOXESFACTORY_H
