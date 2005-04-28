/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id:$
 *
 * @file I3DummyDetectorStatusOriginFactory.h
 * @version $Revision:$
 * @date $Date:$
 * @author pretz
 */

#ifndef I3DUMMYDETECTORSTATUSORIGINFACTORY_H
#define I3DUMMYDETECTORSTSTUSORIGINFACTORY_H

#include "icetray/I3ServiceFactory.h"
#include "phys-source/I3DummyDetectorStatusOrigin.h"

using namespace std;

/**
 * @brief A simple class to install the I3DummyDetectorStatusOrigin 
 * class into the
 * framework
 */
class I3DummyDetectorStatusOriginFactory
: public I3ServiceFactory
{
 public:
  I3DummyDetectorStatusOriginFactory(const I3Context& context);

  virtual ~I3DummyDetectorStatusOriginFactory();

  virtual bool InstallService(I3Services& services);

 private:
  I3DummyDetectorStatusOriginPtr eventOrigin_;

  I3DummyDetectorStatusOriginFactory 
    (const I3DummyDetectorStatusOriginFactory& rhs); 
  I3DummyDetectorStatusOriginFactory operator= 
    (const I3DummyDetectorStatusOriginFactory& rhs); 

  ClassDef(I3DummyDetectorStatusOriginFactory,0);
};

#endif 
