/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3DummyMonitoringOriginFactory.h 7067 2005-04-28 15:04:38Z pretz $
 *
 * @file I3DummyMonitoringOriginFactory.h
 * @version $Revision:$
 * @date $Date: 2005-04-28 11:04:38 -0400 (Thu, 28 Apr 2005) $
 * @author pretz
 */

#ifndef I3DUMMYMONITORINGORIGINFACTORY_H
#define I3DUMMYMONITORINGORIGINFACTORY_H

#include "icetray/I3ServiceFactory.h"
#include "phys-source/I3DummyMonitoringOrigin.h"

using namespace std;

/**
 * @brief A simple class to install the I3DummyMonitoringOrigin class into the
 * framework
 */
class I3DummyMonitoringOriginFactory
: public I3ServiceFactory
{
 public:
  I3DummyMonitoringOriginFactory(const I3Context& context);

  virtual ~I3DummyMonitoringOriginFactory();

  virtual bool InstallService(I3Services& services);

  void Configure();
 private:
  int maxMonitorings_;
  I3DummyMonitoringOriginPtr eventOrigin_;

  I3DummyMonitoringOriginFactory (const I3DummyMonitoringOriginFactory& rhs); 
  I3DummyMonitoringOriginFactory operator= (const I3DummyMonitoringOriginFactory& rhs); 

  ClassDef(I3DummyMonitoringOriginFactory,0);
};

#endif 
