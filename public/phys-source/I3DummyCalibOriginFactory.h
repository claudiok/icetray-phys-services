/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3DummyCalibOriginFactory.h
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#ifndef I3DUMMYCALIBORIGINFACTORY_H
#define I3DUMMYCALIBORIGINFACTORY_H

#include "icetray/I3ServiceFactory.h"
#include "phys-source/I3DummyCalibOrigin.h"

using namespace std;

/**
 * @brief A simple class to install the I3DummyCalibOrigin class into the
 * framework
 */
class I3DummyCalibOriginFactory
: public I3ServiceFactory
{
 public:
  I3DummyCalibOriginFactory(const I3Context& context);

  virtual ~I3DummyCalibOriginFactory();

  virtual bool InstallService(I3Services& services);

 private:
  I3DummyCalibOriginPtr eventOrigin_;

  I3DummyCalibOriginFactory (const I3DummyCalibOriginFactory& rhs); 
  I3DummyCalibOriginFactory operator= (const I3DummyCalibOriginFactory& rhs); 

  ClassDef(I3DummyCalibOriginFactory,0);
};

#endif 
