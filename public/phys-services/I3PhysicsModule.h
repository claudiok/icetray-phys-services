/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3PhysicsModule.h,v 1.2 2004/07/21 15:51:45 pretz Exp $
 *
 * @file I3PhysicsModule.h
 * @version $Revision: 1.2 $
 * @date $Date: 2004/07/21 15:51:45 $
 * @author pretz
 */

#ifndef I3PHYSICSMODULE_H
#define I3PHYSICSMODULE_H

#include "icetray/I3Module.h"
#include "icetray/I3ContextAccess.h"
#include "dataclasses/I3Event.h"
#include "dataclasses/I3Geometry.h"
#include "icetray/I3FrameAccess.h"
#include "I3ParticleDataService.h"
#include "I3Calculator.h"
#include "I3RandomService.h"

using namespace std;

/**
 * @brief A class which provides helper methods to avoid cumbersome syntax.
 * 
 * If a module inherits from this class, it doesn't have to go through
 * the cumbersome I3ContextAccess<>::GetService() syntax.  
 * Can also avoid the I3FrameAccess syntax using the GetEvent and GetGeometry
 * methods
 *
 * @author pretz
 * @todo provide default 'names' for each service to match the default names
 * the services are created with
 * @todo add methods to access other stream objects when they are defined
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

  /**
   * Gets an event out of a frame.  Just a helper method to simplify the
   * syntax.
   * @return an I3Event that is in the frame
   * @param frame the frame that you want the event out of.
   * @param name the name of the event in the frame, defaults to "Physics"
   */
  I3Event& GetEvent(I3Frame& frame,const string& name = "Physics")
    {
      return I3FrameAccess<I3Event>::Get(frame,name);
    }

  /**
   * Gets the geometry out of the frame.  Just a helper method to simplify the
   * syntax
   * @return an I3Geometry that is in the frame
   * @param frame the frame that you want the event out of
   */
  I3Geometry& GetGeometry(I3Frame& frame,const string& name="Geometry")
    {
      return I3FrameAccess<I3Geometry>::Get(frame,name);
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
