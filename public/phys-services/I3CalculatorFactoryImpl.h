#ifndef I3CALCULATORFACTORYIMPL_H
#define I3CALCULATORFACTORYIMPL_H
/*
 * class: I3CalculatorFactoryImpl
 *
 * Version $Id: I3CalculatorFactoryImpl.h,v 1.1.2.2 2004/09/24 19:12:24 pretz Exp $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Header files

#ifndef I3TYPES
#include "icetray/I3types"
#endif // I3TYPE

#include "phys-services/I3Calculator.h"

// forward declarations

class I3Context;
class I3Services;

// superclasses

#include "icetray/I3ServiceFactory.h"

// namespace declarations

using namespace std;

/**
 * This class installs a I3CalculatorFactoryImpl.
 *
 * @version $Id: I3CalculatorFactoryImpl.h,v 1.1.2.2 2004/09/24 19:12:24 pretz Exp $
 * @author pretz
 */
class I3CalculatorFactoryImpl
: public I3ServiceFactory
{
 public:

  // Constructors and destructor

  I3CalculatorFactoryImpl(const I3Context& context);

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
  virtual Bool_t InstallService(I3Services& services);

 private:

  // private constructors, destructor and assignment

  I3CalculatorFactoryImpl
    (const I3CalculatorFactoryImpl& rhs); // stop default
  I3CalculatorFactoryImpl operator=
    (const I3CalculatorFactoryImpl& rhs); // stop default

  // instance member data

  I3CalculatorPtr fCalculator;

  // ROOT macros
  ClassDef(I3CalculatorFactoryImpl,0);
};

#endif // ROOTI3BOXESFACTORY_H
