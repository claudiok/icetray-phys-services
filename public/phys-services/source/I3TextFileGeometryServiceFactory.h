#ifndef I3TRANDOMSERVICEFACTORY_H
#define I3TRANDOMSERVICEFACTORY_H
/*
 * class: I3TextFileGeometryServiceFactory
 *
 * Version $Id: I3TextFileGeometryServiceFactory.h 11148 2005-10-03 21:55:04Z pretz $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

// Header files


// forward declarations

class I3Context;
class I3Services;

#include "icetray/I3ServiceFactory.h"
class I3TextFileGeometryService;

using namespace std;

class I3TextFileGeometryServiceFactory
: public I3ServiceFactory
{
 public:

  I3TextFileGeometryServiceFactory(const I3Context& context);

  virtual ~I3TextFileGeometryServiceFactory();

  virtual bool InstallService(I3Services& services);

  virtual void Configure();

 private:

  shared_ptr<I3TextFileGeometryService> geometry_;

  string amandaFile_;
  string icecubeFile_;

  I3TextFileGeometryServiceFactory
    (const I3TextFileGeometryServiceFactory& rhs); // stop default
  I3TextFileGeometryServiceFactory operator=
    (const I3TextFileGeometryServiceFactory& rhs); // stop default


   SET_LOGGER("I3TextFileGeometryServiceFactory");
};

#endif 
