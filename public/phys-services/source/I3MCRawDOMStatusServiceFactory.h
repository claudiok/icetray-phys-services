#ifndef I3MCRAWDOMSTATUSSERVICEFACTORY_H
#define I3MCRAWDOMSTATUSSERVICEFACTORY_H
/*
 * class: I3TextFileGeometryServiceFactory
 *
 * Version $Id: I3TextFileGeometryServiceFactory.h 11148 2005-10-03 21:55:04Z pretz $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

class I3Context;

#include "icetray/I3ServiceFactory.h"
class I3MCRawDOMStatusService;

using namespace std;

class I3MCRawDOMStatusServiceFactory
: public I3ServiceFactory
{
 public:

  I3MCRawDOMStatusServiceFactory(const I3Context& context);

  virtual ~I3MCRawDOMStatusServiceFactory();

  virtual bool InstallService(I3Context& services);

  virtual void Configure();

 private:

  shared_ptr<I3MCRawDOMStatusService> status_;

  I3MCRawDOMStatusServiceFactory
    (const I3MCRawDOMStatusServiceFactory& rhs); // stop default
  I3MCRawDOMStatusServiceFactory operator=
    (const I3MCRawDOMStatusServiceFactory& rhs); // stop default


   SET_LOGGER("I3MCRawDOMStatusServiceFactory");
};

#endif 
