/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3PhysicsModule.h,v 1.1 2004/07/16 19:41:05 pretz Exp $
 *
 * @file I3PhysicsModule.h
 * @version $Revision: 1.1 $
 * @date $Date: 2004/07/16 19:41:05 $
 * @author pretz
 */

#ifndef I3PHYSICSMODULE_H
#define I3PHYSICSMODULE_H

#include "icetray/I3Module.h"
#include "icetray/I3ContextAccess.h"
#include "I3ParticleDataService.h"
#include "I3Calculator.h"
#include "I3RandomService.h"

/**
 * A class which provides helper methods to access standard services.
 * If a module inherits from this class, it doesn't have to go through
 * the cumbersome I3ContextAccess<>::GetService() syntax
 *
 * @author pretz
 * @todo provide default 'names' for each service to match the default names
 * the services are created with
 */
class I3PhysicsModule : public I3Module
{
 public:
  /**
   * This is the only constructor that should be used for this module
   * @param ctx the context that this module is built with
   */
  I3PhysicsModule(I3Context& ctx) : I3Module(ctx){}

  /**
   * destructor
   */
  virtual ~I3PhysicsModule(){}

  /**
   * returns a reference to the particle data service
   * @return a reference to the particle data serve that a module is
   * using 
   * @param name the name of the instance of the service requested.
   */
  I3ParticleDataService& GetParticleData(const string& name)
    {
      return I3ContextAccess<I3ParticleDataService>::
	GetService(GetContext(),name);
    }

  /**
   * returns a reference to the calculator service
   * @return a reference to the calculator service that this
   * module is using
   * @param name the name of the instance of the service requested
   */
  I3Calculator& GetCalculator(const string& name)
    {
      return I3ContextAccess<I3Calculator>::
	GetService(GetContext(),name);
    }

  /**
   * returns a reference to the random number service
   * @return a reference to the random number service
   * @param name the name of the service to find
   */
  I3RandomService& GetRandom(const string& name)
    {
      return I3ContextAccess<I3RandomService>::
	GetService(GetContext(),name);
    }

 private:

  // default, copy and assignment private
  I3PhysicsModule();
  I3PhysicsModule(const I3PhysicsModule&);
  I3PhysicsModule operator=(const I3PhysicsModule&);

  // ROOT macro
  ClassDef(I3PhysicsModule,0);
};


#endif
