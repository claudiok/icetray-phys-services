/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3PhysicsModule.h,v 1.5 2004/08/06 15:06:09 pretz Exp $
 *
 * @file I3PhysicsModule.h
 * @version $Revision: 1.5 $
 * @date $Date: 2004/08/06 15:06:09 $
 * @author pretz
 */

#ifndef I3PHYSICSMODULE_H
#define I3PHYSICSMODULE_H

#include "icetray/I3Module.h"
#include "icetray/I3ContextAccess.h"
#include "dataclasses/I3MCEvent.h"
#include "dataclasses/I3MCEventHeader.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3GeometryHeader.h"
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
  I3ParticleDataService& GetParticleData(const string& name=
					 I3ParticleDataService::DefaultName())
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
  I3Calculator& GetCalculator(const string& name=
			      I3Calculator::DefaultName())
    {
      return I3ContextAccess<I3Calculator>::
	GetService(GetContext(),name);
    }

  /**
   * returns a reference to the random number service
   * @return a reference to the random number service
   * @param name the name of the service to find
   */
  I3RandomService& GetRandom(const string& name=I3RandomService::DefaultName())
    {
      return I3ContextAccess<I3RandomService>::
	GetService(GetContext(),name);
    }

  /**
   * checks to see if the frame has a monte-carlo event in it.
   * @return true if an event is present, false if not
   * @param frame the frame we want to check
   * @param name the name of the event in the frame.  Defaults to 'Physics'
   */
  Bool_t HasMCEvent(I3Frame& frame, const string& name = "Physics")
    {
      return I3FrameAccess<I3MCEvent>::Exists(frame,name);
    }

  /**
   * Gets a monte-carlo event out of a frame.  Just a helper method to 
   * simplify the
   * syntax.
   * @return an I3MCEvent that is in the frame
   * @param frame the frame that you want the event out of.
   * @param name the name of the event in the frame, defaults to "Physics"
   */
  I3MCEvent& GetMCEvent(I3Frame& frame,const string& name = "Physics")
    {
      return I3FrameAccess<I3MCEvent>::Get(frame,name);
    }

  /**
   * Puts a monte-carlo event in the frame.  
   * Just a helper method to simplify the syntax
   * @param frame the frame to put the event into
   * @param event the event to put into the frame
   * @param name the name of the event in the frame.  Defaults to 'Physics'
   * @return true if it is successful, false if otherwise
   */
  Bool_t PutMCEvent(I3Frame& frame,I3MCEvent* event,
		    const string& name="Physics")
    {
      return I3FrameAccess<I3MCEvent>::Put(frame,event,name);
    }

   /**
   * checks to see if the frame has an event in it.
   * @return true if an event is present, false if not
   * @param frame the frame we want to check
   * @param name the name of the event in the frame.  Defaults to 'Physics'
   */
  Bool_t HasEvent(I3Frame& frame, const string& name = "Physics")
    {
      return I3FrameAccess<I3Event>::Exists(frame,name);
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
   * Puts an event in the frame.  Just a helper method to simplify the syntax
   * @param frame the frame to put the event into
   * @param event the event to put into the frame
   * @param name the name of the event in the frame.  Defaults to 'Physics'
   * @return true if it is successful, false if otherwise
   */
  Bool_t PutEvent(I3Frame& frame,I3Event* event,const string& name="Physics")
  {
    return I3FrameAccess<I3Event>::Put(frame,event,name);
  }

  /**
   * checks to see if the frame has a monte-carlo event headerin it.
   * @return true if an event headeris present, false if not
   * @param frame the frame we want to check
   * @param name the name of the event header in the frame.  Defaults to
   * 'PhysicsHeader'
   */
  Bool_t HasMCEventHeader(I3Frame& frame,const string& name="PhysicsHeader")
    {
      return I3FrameAccess<I3MCEventHeader>::Exists(frame,name);
    }

  /**
   * Gets an monte-carlo event header out of a frame.  Just a helper method 
   * to simplify syntax
   * @return the event header in the frame
   * @param frame the frame that you want the event header out of.
   * @param name the name of the event header in the frame.  Defaults to
   * 'PhysicsHeader'
   */
  I3MCEventHeader& GetMCEventHeader(I3Frame& frame,
                                const string& name="PhysicsHeader")
    {
      return I3FrameAccess<I3MCEventHeader>::Get(frame,name);
    }

  /**
   * Puts an event header in the frame.  Just a helper method to
   * simplify the syntax
   * @param frame the frame to put the event header into
   * @param header the event header to put into the frame
   * @param name the name of the header in the frame.
   * Defaults to 'PhysicsHeader'
   * @return true if it is successful, false if otherwise
   */
  Bool_t PutMCEventHeader(I3Frame& frame,
                        I3MCEventHeader* header,
                        const string& name="PhysicsHeader")
    {
      return I3FrameAccess<I3MCEventHeader>::Put(frame,header,name);
    }


  /**
   * checks to see if the frame has an event headerin it.
   * @return true if an event headeris present, false if not
   * @param frame the frame we want to check
   * @param name the name of the event header in the frame.  Defaults to 
   * 'PhysicsHeader'
   */ 
  Bool_t HasEventHeader(I3Frame& frame,const string& name="PhysicsHeader")
    {
      return I3FrameAccess<I3EventHeader>::Exists(frame,name);
    }

  /**
   * Gets an event header out of a frame.  Just a helper method to simplify
   * syntax
   * @return the event header in the frame
   * @param frame the frame that you want the event header out of.
   * @param name the name of the event header in the frame.  Defaults to 
   * 'PhysicsHeader'
   */
  I3EventHeader& GetEventHeader(I3Frame& frame,
				const string& name="PhysicsHeader")
    {
      return I3FrameAccess<I3EventHeader>::Get(frame,name);
    }

  /**
   * Puts an event header in the frame.  Just a helper method to 
   * simplify the syntax
   * @param frame the frame to put the event header into
   * @param header the event header to put into the frame
   * @param name the name of the header in the frame.  
   * Defaults to 'PhysicsHeader'
   * @return true if it is successful, false if otherwise
   */
  Bool_t PutEventHeader(I3Frame& frame,
			I3EventHeader* header,
			const string& name="PhysicsHeader")
  {
    return I3FrameAccess<I3EventHeader>::Put(frame,header,name);
  }

  /**
   * Checks to see if a frame has a geometry in it
   * @param frame the frame we want to check
   * @param name the name of the geometry in the frame
   * @return true if the frame has a geometry, false if otherwise
   */
  Bool_t HasGeometry(I3Frame& frame,const string& name="Geometry")
  {
    return I3FrameAccess<I3Geometry>::Exists(frame,name);
  }

  /**
   * Gets the geometry out of the frame.  Just a helper method to simplify the
   * syntax
   * @return an I3Geometry that is in the frame
   * @param frame the frame that you want the geometry out of
   */
  I3Geometry& GetGeometry(I3Frame& frame,const string& name="Geometry")
    {
      return I3FrameAccess<I3Geometry>::Get(frame,name);
    }

  /**
   * Puts a geometry in the frame.  Just a helper method to simplify the syntax
   * @param frame the frame to put the geometry into
   * @param geometry the geometry to put into the frame
   * @param name the name of the geometry in the frame.  Defaults to 'Geometry'
   * @return true if it is successful, false if otherwise
   */
  Bool_t PutGeometry(I3Frame& frame,
		     I3Geometry* geometry,
		     const string& name="Geometry")
    {
      return I3FrameAccess<I3Geometry>::Put(frame,geometry,name);
    }

  /*
   * Checks to see if a frame has a geometry headerin it
   * @param frame the frame we want to check
   * @param name the name of the geometry header in the frame
   * @return true if the frame has a geometry header, false if otherwise
   */
  Bool_t HasGeometryHeader(I3Frame& frame,const string& name="GeometryHeader")
    {
      return I3FrameAccess<I3GeometryHeader>::Exists(frame,name);
    }

  /**
   * Gets the geometry header out of the frame.  Just a helper method to 
   * simplify the syntax.  
   * @return an I3GeometryHeader that is in the frame
   * @param frame the frame that you want the geometry header out of.
   * @param name the name of the geometry header in the frame.  Defaults
   * to 'GeometryHeader'
   */
  I3GeometryHeader& GetGeometryHeader(I3Frame& frame, 
				      const string& name="GeometryHeader")
    {
      return I3FrameAccess<I3GeometryHeader>::Get(frame,name);
    }

  /**
   * Puts a geometry header in the frame.  Just a helper method to 
   * simplify the syntax
   * @param frame the frame to put the geometry header into
   * @param header the geometry header to put into the frame
   * @param name the name of the header in the frame.  
   * Defaults to 'GeometryHeader'
   * @return true if it is successful, false if otherwise
   */
  Bool_t PutEventHeader(I3Frame& frame,
			I3GeometryHeader* header,
			const string& name="GeometryHeader")
  {
    return I3FrameAccess<I3GeometryHeader>::Put(frame,header,name);
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
