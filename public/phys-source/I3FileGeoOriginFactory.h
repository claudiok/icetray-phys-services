#ifndef I3FILEGEOORIGINFACTORY_H
#define I3FILEGEOORIGINFACTORY_H

#include "icetray/I3ServiceFactory.h"
#include "phys-source/I3FileGeoOrigin.h"

using namespace std;

/**
 * @brief A simple class to install the I3FileGeoOrigin class into the
 * framework
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 * @ingroup experimentalphysservices
 */
class I3FileGeoOriginFactory
: public I3ServiceFactory
{
 public:
  I3FileGeoOriginFactory(const I3Context& context);

  virtual ~I3FileGeoOriginFactory();

  void Configure();

  virtual bool InstallService(I3Services& services);

 private:
  I3FileGeoOriginPtr origin_;
  string amaGeoFile_;
  string icecubeGeoFile_;

  I3FileGeoOriginFactory (const I3FileGeoOriginFactory& rhs); 
  I3FileGeoOriginFactory operator= (const I3FileGeoOriginFactory& rhs); 

  ClassDef(I3FileGeoOriginFactory,0);
};

#endif 
