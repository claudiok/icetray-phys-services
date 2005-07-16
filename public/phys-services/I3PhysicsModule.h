/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3PhysicsModule.h
 * @version $Revision: 1.15 $
 * @date $Date$
 * @author pretz
 */

#ifndef I3PHYSICSMODULE_H
#define I3PHYSICSMODULE_H

#include "icetray/I3Module.h"
#include "icetray/I3ContextAccess.h"
#include "icetray/I3FrameAccess.h"
#include "icetray/I3Frame.h"
#include "I3ParticleDataService.h"
#include "I3RandomService.h"

class I3MCEvent;
class I3MCEventHeader;
class I3Event;
class I3EventHeader;
class I3Calibration;
class I3CalibrationHeader;
class I3Geometry;
class I3GeometryHeader;
class I3DetectorStatus;
class I3DetectorStatusHeader;


typedef shared_ptr<I3MCEvent> I3MCEventPtr;
typedef shared_ptr<I3MCEventHeader> I3MCEventHeaderPtr;

typedef shared_ptr<I3Event> I3EventPtr;
typedef shared_ptr<I3EventHeader> I3EventHeaderPtr;

typedef shared_ptr<I3Geometry> I3GeometryPtr;
typedef shared_ptr<I3GeometryHeader> I3GeometryHeaderPtr;

typedef shared_ptr<I3Calibration> I3CalibPtr;
typedef shared_ptr<I3CalibrationHeader> I3CalibrationHeaderPtr;

typedef shared_ptr<I3DetectorStatus> I3DetectorStatusPtr;
typedef shared_ptr<I3DetectorStatusHeader> I3DetectorStatusHeaderPtr;


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
					 I3ParticleDataService::DefaultName());
  /**
   * returns a reference to the random number service
   * @return a reference to the random number service
   * @param name the name of the service to find
   */
  I3RandomService& GetRandom(const string& name=I3RandomService::DefaultName());

  /**
   * checks to see if the frame has a monte-carlo event in it.
   * @return true if an monte-carlo event is present, false if not.
   * @param frame the frame we want to check.
   * @param name the name of the monte-carlo event in the frame.
   * Defaults to 'Physics'.
   */
  bool HasMCEvent(I3Frame& frame, const string& name = "Physics");

  /**
   * Gets a monte-carlo event out of a frame.  Just a helper method to 
   * simplify the syntax.
   * @return the monte-carlo event that is in the frame.
   * @param frame the frame that you want the event out of.
   * @param name the name of the event in the frame.
   * Defaults to "Physics".
   */
  I3MCEvent& GetMCEvent(I3Frame& frame,const string& name = "Physics");

  /**
   * Puts a monte-carlo event in the frame.  
   * Just a helper method to simplify the syntax.
   * @param frame the frame to put the event into.
   * @param event the monte-carlo event to put into the frame.
   * @param name the name of the monte-carlo event in the frame.
   * Defaults to 'Physics'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutMCEvent(I3Frame& frame,I3MCEventPtr event,
		  const string& name="Physics");

   /**
   * checks to see if the frame has an event in it.
   * @return true if an event is present, false if not.
   * @param frame the frame we want to check.
   * @param name the name of the event in the frame.
   * Defaults to 'Physics'.
   */
  bool HasEvent(I3Frame& frame, const string& name = "Physics");

  /**
   * Gets an event out of a frame.  Just a helper method to simplify the
   * syntax.
   * @return an I3Event that is in the frame.
   * @param frame the frame that you want the event out of.
   * @param name the name of the event in the frame.
   * Defaults to "Physics".
   */
  I3Event& GetEvent(I3Frame& frame,const string& name = "Physics");

  /**
   * Puts an event in the frame.
   * Just a helper method to simplify the syntax.
   * @param frame the frame to put the event into.
   * @param event the event to put into the frame.
   * @param name the name of the event in the frame.
   * Defaults to 'Physics'
   * @return true if it is successful, false if otherwise.
   */
  bool PutEvent(I3Frame& frame,I3EventPtr event,const string& name="Physics");

  /**
   * checks to see if the frame has a monte-carlo event header in it.
   * @return true if an monte-carlo event header is present, false if not.
   * @param frame the frame we want to check.
   * @param name the name of the monte-carlo event header in the frame.
   * Defaults to 'PhysicsHeader'.
   */
  bool HasMCEventHeader(I3Frame& frame,const string& name="PhysicsHeader");

  /**
   * Gets an monte-carlo event header out of a frame.  Just a helper method 
   * to simplify syntax.
   * @return the monte-carlo event header in the frame.
   * @param frame the frame that you want the event header out of.
   * @param name the name of the event header in the frame.  Defaults to
   * 'PhysicsHeader'.
   */
  I3MCEventHeader& GetMCEventHeader(I3Frame& frame,
				    const string& name="PhysicsHeader");

  /**
   * Puts an monte-carlo event header in the frame.
   * Just a helper method to simplify the syntax.
   * @param frame the frame to put the event header into.
   * @param header the monte-carlo event header to put into the frame.
   * @param name the name of the header in the frame.
   * Defaults to 'PhysicsHeader'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutMCEventHeader(I3Frame& frame,
                        I3MCEventHeaderPtr header,
                        const string& name="PhysicsHeader");

  /**
   * checks to see if the frame has an event header in it.
   * @return true if an event headeris present, false if not
   * @param frame the frame we want to check.
   * @param name the name of the event header in the frame. Defaults to 
   * 'PhysicsHeader'.
   */ 
  bool HasEventHeader(I3Frame& frame,const string& name="PhysicsHeader");

  /**
   * Gets an event header out of a frame.  Just a helper method to simplify
   * syntax.
   * @return the event header in the frame.
   * @param frame the frame that you want the event header out of.
   * @param name the name of the event header in the frame.  Defaults to 
   * 'PhysicsHeader'.
   */
  I3EventHeader& GetEventHeader(I3Frame& frame,
				const string& name="PhysicsHeader");

  /**
   * Puts an event header in the frame.  Just a helper method to 
   * simplify the syntax.
   * @param frame the frame to put the event header into
   * @param header the event header to put into the frame
   * @param name the name of the header in the frame.  
   * Defaults to 'PhysicsHeader'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutEventHeader(I3Frame& frame,
			I3EventHeaderPtr header,
		      const string& name="PhysicsHeader");

  /*
   * checks to see if a frame has a calibration in it.
   * @param frame the frame we want to check.
   * @param name the name of the calibration in the frame. Defaults to
   * 'Calibration'.
   * @return true if the frame has a calibration, false if otherwise.
   */
  bool HasCalibration(I3Frame& frame, const string& name = "Calibration");
    
  /**
   * Puts a calibration in the frame. Just a helper method to
   * simplify the syntax.
   * @param frame the frame to put the claibration  into.
   * @param  the calibration to put into the frame.
   * @param name the name of the calibration  in the frame.
   * Defaults to 'Calibration'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutCalibration(I3Frame& frame,
			I3CalibPtr calib,
		      const string& name = "Calibration");

  /**
   * Gets the calibration out of the frame. Just a helper method to 
   * simplify the syntax.  
   * @return the calibration that is in the frame.
   * @param frame the frame that you want the calibration out of.
   * @param name the name of the calibration in the frame. Defaults
   * to 'Calibration'.
   */
  I3Calibration& GetCalibration(I3Frame& frame, const string& name = "Calibration");

  /**
   * checks to see if a frame has a geometry in it.
   * @param frame the frame we want to check.
   * @param name the name of the geometry in the frame. Defaults
   * to 'Geometry'.
   * @return true if the frame has a geometry, false if otherwise.
   */
  bool HasGeometry(I3Frame& frame,const string& name="Geometry");

  /**
   * Gets the geometry out of the frame.  Just a helper method to simplify the
   * syntax.
   * @return the geometry that is in the frame.
   * @param frame the frame that you want the geometry out of.
   * @param name the name of the geometry in the frame. Defaults
   * to 'Geometry'.
   */
  I3Geometry& GetGeometry(I3Frame& frame,const string& name="Geometry");

  /**
   * Puts a geometry in the frame.  Just a helper method to simplify the syntax.
   * @param frame the frame to put the geometry into.
   * @param geometry the geometry to put into the frame.
   * @param name the name of the geometry in the frame.  Defaults to 'Geometry'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutGeometry(I3Frame& frame,
		     I3GeometryPtr geometry,
		   const string& name="Geometry");
		   
  /*
   * checks to see if a frame has a geometry header in it.
   * @param frame the frame we want to check.
   * @param name the name of the geometry header in the frame. Defaults to
   * 'GeometryHeader'.
   * @return true if the frame has a geometry header, false if otherwise.
   */
  bool HasGeometryHeader(I3Frame& frame,const string& name="GeometryHeader");
   
  /**
   * Gets the geometry header out of the frame.  Just a helper method to 
   * simplify the syntax.  
   * @return the geometry header that is in the frame.
   * @param frame the frame that you want the geometry header out of.
   * @param name the name of the geometry header in the frame.  Defaults
   * to 'GeometryHeader'.
   */
  I3GeometryHeader& GetGeometryHeader(I3Frame& frame, 
				      const string& name="GeometryHeader");

  /**
   * Puts a geometry header in the frame.  Just a helper method to 
   * simplify the syntax.
   * @param frame the frame to put the geometry header into.
   * @param header the geometry header to put into the frame.
   * @param name the name of the geometry header in the frame.  
   * Defaults to 'GeometryHeader'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutGeometryHeader(I3Frame& frame,
			I3GeometryHeaderPtr header,
			 const string& name="GeometryHeader");

  /*
   * checks to see if a frame has a calibration header in it.
   * @param frame the frame we want to check.
   * @param name the name of the calibration header in the frame. Defaults to
   * 'CalibrationHeader'.
   * @return true if the frame has a calibration header, false if otherwise.
   */
  bool HasCalibrationHeader(I3Frame& frame,const string& name="CalibrationHeader");
      
  /**
   * Gets the calibration header out of the frame.  Just a helper method to 
   * simplify the syntax.  
   * @return the calibration header that is in the frame.
   * @param frame the frame that you want the calibration header out of.
   * @param name the name of the calibration header in the frame.  Defaults
   * to 'CalibrationHeader'.
   */
  I3CalibrationHeader& GetCalibrationHeader(I3Frame& frame, 
					    const string& name="CalibrationHeader");
					    
  /**
   * Puts a calibration header in the frame.  Just a helper method to
   * simplify the syntax.
   * @param frame the frame to put the claibration header into.
   * @param header the calibration header to put into the frame.
   * @param name the name of the calibration header in the frame.
   * Defaults to 'CalibrationHeader'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutCalibrationHeader(I3Frame& frame,
			      I3CalibrationHeaderPtr header,
			    const string& name="CalibrationHeader");
			    
  /**
   * checks to see if the frame has a detector status in it.
   * @return true if an detector status is present, false if not.
   * @param frame the frame we want to check.
   * @param name the name of the detector status in the frame.  
   * Defaults to 'DetectorStatus'.
   */
  bool HasDetectorStatus(I3Frame& frame, 
			 const string& name = "DetectorStatus");

  /**
   * Gets a detector status out of a frame.  Just a helper method to 
   * simplify the syntax.
   * @return the detector status that is in the frame.
   * @param frame the frame that you want the detector status out of.
   * @param name the name of the detector status in the frame.
   * Defaults to "DetectorStatus".
   */
  I3DetectorStatus& GetDetectorStatus(I3Frame& frame,
				      const string& name = "DetectorStatus");

  /**
   * Puts a  detector status in the frame.  
   * Just a helper method to simplify the syntax.
   * @param frame the frame to put the detector status into.
   * @param status the detector status to put into the frame.
   * @param name the name of the detector status in the frame.  
   * Defaults to 'DetectorStatus'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutDetectorStatus(I3Frame& frame,I3DetectorStatusPtr status,
			 const string& name="DetectorStatus");

  /**
   * checks to see if the frame has a  detector status header in it.
   * @return true if an detector status header is present, false if not.
   * @param frame the frame we want to check.
   * @param name the name of the detector status header in the frame. Defaults to
   * 'DetectorStatusHeader'.
   */
  bool HasDetectorStatusHeader(I3Frame& frame,
			       const string& name="DetectorStatusHeader");

  /**
   * Gets an detector status header out of a frame.  Just a helper method 
   * to simplify syntax.
   * @return the detector status header in the frame.
   * @param frame the frame that you want the detector status header out of.
   * @param name the name of the detector status header in the frame. Defaults to
   * 'DetectorStatusHeader'.
   */
  I3DetectorStatusHeader& GetDetectorStatusHeader(I3Frame& frame,
						  const string& name="DetectorStatusHeader");

  /**
   * Puts an detector status header in the frame.  Just a helper method to
   * simplify the syntax.
   * @param frame the frame to put the detector status header into.
   * @param header the detector status header to put into the frame.
   * @param name the name of the detector status header in the frame.
   * Defaults to 'DetectorStatusHeader'.
   * @return true if it is successful, false if otherwise.
   */
  bool PutDetectorStatusHeader(I3Frame& frame,
			  I3DetectorStatusHeaderPtr header,
			       const string& name="DetectorStatusHeader");

  /**
   * Checks to see if a frame has a monitoring in it
   * @param frame the frame we want to check
   * @param name the name of the monitoring in the frame
   * @return true if the frame has a monitoring, false if otherwise
   */
/*   bool HasMonitoring(I3Frame& frame,const string& name="Monitoring") */
/*     { */
/*       return I3FrameAccess<I3Monitoring>::Exists(frame,name); */
/*     } */
  
  /**
   * Gets the monitoring out of the frame.  Just a helper method to 
   * simplify the
   * syntax
   * @return an I3Monitoring that is in the frame
   * @param frame the frame that you want the monitoring out of
   */
/*   I3Monitoring& GetMonitoring(I3Frame& frame,const string& name="Monitoring") */
/*     { */
/*       return I3FrameAccess<I3Monitoring>::Get(frame,name); */
/*     } */
  
  /**
   * Puts a monitoring in the frame.  Just a helper method to simplify 
   * the syntax
   * @param frame the frame to put the monitoring into
   * @param monitoring the monitoring to put into the frame
   * @param name the name of the monitoring in the frame.  Defaults to 
   * 'Monitoring'
   * @return true if it is successful, false if otherwise
   */
/*   bool PutMonitoring(I3Frame& frame, */
/* 		       I3MonitoringPtr monitoring, */
/* 		       const string& name="Monitoring") */
/*     { */
/*       return I3FrameAccess<I3Monitoring>::Put(frame,monitoring,name); */
/*     } */
  
  /*
   * Checks to see if a frame has a monitoring header in it
   * @param frame the frame we want to check
   * @param name the name of the monitoring header in the frame
   * @return true if the frame has a monitoring header, false if otherwise
   */
/*   bool HasMonitoringHeader(I3Frame& frame, */
/* 			     const string& name="MonitoringHeader") */
/*     { */
/*       return I3FrameAccess<I3MonitoringHeader>::Exists(frame,name); */
/*     } */
  
  /**
   * Gets the monitoring header out of the frame.  Just a helper method to 
   * simplify the syntax.  
   * @return an I3MonitoringHeader that is in the frame
   * @param frame the frame that you want the monitoring header out of.
   * @param name the name of the monitoring header in the frame.  Defaults
   * to 'MonitoringHeader'
   */
/*   I3MonitoringHeader& GetMonitoringHeader(I3Frame& frame,  */
/* 					  const string& name= */
/* 					  "MonitoringHeader") */
/*     { */
/*       return I3FrameAccess<I3MonitoringHeader>::Get(frame,name); */
/*     } */
  
  /**
   * Puts a evemt header in the frame.  Just a helper method to 
   * simplify the syntax
   * @param frame the frame to put the monitoring header into
   * @param header the monitoring header to put into the frame
   * @param name the name of the header in the frame.  
   * Defaults to 'MonitoringHeader'
   * @return true if it is successful, false if otherwise
   */
/*   bool PutMonitoringHeader(I3Frame& frame, */
/* 			     I3MonitoringHeaderPtr header, */
/* 			     const string& name="MonitoringHeader") */
/*     { */
/*       return I3FrameAccess<I3MonitoringHeader>::Put(frame,header,name); */
/*     } */
  
 private:
  
  // default, copy and assignment private
  I3PhysicsModule();
  I3PhysicsModule(const I3PhysicsModule&);
  I3PhysicsModule operator=(const I3PhysicsModule&);

	// okay, following methods help to get rid of the problems if someone
	// puts an I3MCEvent(Header) into a frame via I3FrameAccess<I3MCEvent>
	// instead of using I3FrameAccess<I3Event> or PutMCEvent.
	I3EventPtr
		GetEvent(I3Frame& frame, const string& name, bool strict);
	I3EventHeaderPtr
		GetEventHeader(I3Frame& frame, const string& name, bool strict);
	I3MCEventPtr
		GetMCEvent(I3Frame& frame, const string& name, bool strict);
	I3MCEventHeaderPtr
		GetMCEventHeader(I3Frame& frame, const string& name, bool strict);
	

  // ROOT macro
  ClassDef(I3PhysicsModule,0);
};

#endif
