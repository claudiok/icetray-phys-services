/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3DummyGeoOriginFactory.h
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#ifndef I3DUMMYGEOORIGINFACTORY_H
#define I3DUMMYGEOORIGINFACTORY_H

#include "icetray/I3ServiceFactory.h"
#include "phys-source/I3DummyGeoOrigin.h"

using namespace std;

/**
 * @brief A simple class to install the I3DummyGeoOrigin class into the
 * framework
 */
class I3DummyGeoOriginFactory
: public I3ServiceFactory
{
 public:
  I3DummyGeoOriginFactory(const I3Context& context);

  virtual ~I3DummyGeoOriginFactory();

  virtual bool InstallService(I3Services& services);

 private:
  I3DummyGeoOriginPtr eventOrigin_;

  I3DummyGeoOriginFactory (const I3DummyGeoOriginFactory& rhs); 
  I3DummyGeoOriginFactory operator= (const I3DummyGeoOriginFactory& rhs); 

  ClassDef(I3DummyGeoOriginFactory,0);
};

#endif 
