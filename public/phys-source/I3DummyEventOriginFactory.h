#ifndef I3DUMMYEVENTORIGINFACTORY_H
#define I3DUMMYEVENTORIGINFACTORY_H

#include "icetray/I3ServiceFactory.h"
#include "phys-source/I3DummyEventOrigin.h"

using namespace std;

/**
 * @brief A simple class to install the I3DummyEventOrigin class into the
 * framework
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3DummyEventOriginFactory
: public I3ServiceFactory
{
 public:
  I3DummyEventOriginFactory(const I3Context& context);

  virtual ~I3DummyEventOriginFactory();

  virtual Bool_t InstallService(I3Services& services);

 private:
  I3DummyEventOriginPtr eventOrigin_;

  I3DummyEventOriginFactory (const I3DummyEventOriginFactory& rhs); 
  I3DummyEventOriginFactory operator= (const I3DummyEventOriginFactory& rhs); 

  ClassDef(I3DummyEventOriginFactory,0);
};

#endif 
