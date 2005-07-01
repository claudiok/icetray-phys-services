#include "phys-services/I3PhysicsModule.h"

//#include "icetray/I3Module.h"
//#include "icetray/I3ContextAccess.h"
#include "dataclasses/I3MCEvent.h"
#include "dataclasses/I3MCEventHeader.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3Calibration.h"
#include "dataclasses/I3CalibrationHeader.h"
#include "dataclasses/I3GeometryHeader.h"
#include "dataclasses/I3DetectorStatus.h"
#include "dataclasses/I3DetectorStatusHeader.h"
//#include "dataclasses/I3Monitoring.h"
//#include "dataclasses/I3MonitoringHeader.h"
//#include "icetray/I3FrameAccess.h"
//#include "I3ParticleDataService.h"
//#include "I3RandomService.h"

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
/**
 * checks to see if the frame has a monte-carlo event in it.
 * @return true if an event is present, false if not
 * @param frame the frame we want to check
 * @param name the name of the event in the frame.  Defaults to 'Physics'
 */

I3ParticleDataService& I3PhysicsModule::GetParticleData(const string& name)
{
  return I3ContextAccess<I3ParticleDataService>::
    GetService(GetContext(),name);
}

/**
 * returns a reference to the random number service
 * @return a reference to the random number service
 * @param name the name of the service to find
 */
I3RandomService& I3PhysicsModule::GetRandom(const string& name)
{
  return I3ContextAccess<I3RandomService>::
    GetService(GetContext(),name);
}


bool I3PhysicsModule::HasMCEvent(I3Frame& frame, const string& name)
{
  if(I3FrameAccess<I3Event>::Exists(frame,name))
    {
      I3Event& event = I3FrameAccess<I3Event>::Get(frame,name);
      I3MCEvent* mcevent = dynamic_cast<I3MCEvent*>(&event);
      if(mcevent)
	return true;
    }
  return false;
}

/**
 * Gets a monte-carlo event out of a frame.  Just a helper method to 
 * simplify the
 * syntax.
 * @return an I3MCEvent that is in the frame
 * @param frame the frame that you want the event out of.
 * @param name the name of the event in the frame, defaults to "Physics"
 */
I3MCEvent& I3PhysicsModule::GetMCEvent(I3Frame& frame,const string& name)
{
  I3EventPtr eventPtr = frame.Get<I3EventPtr>(name);
  I3MCEventPtr mcEventPtr = dynamic_pointer_cast<I3MCEvent>(eventPtr);
  if(!mcEventPtr) log_fatal("failed to cast I3EventPtr to I3MCEventPtr");
  return *mcEventPtr;
}

/**
 * Puts a monte-carlo event in the frame.  
 * Just a helper method to simplify the syntax
 * @param frame the frame to put the event into
 * @param event the event to put into the frame
 * @param name the name of the event in the frame.  Defaults to 'Physics'
 * @return true if it is successful, false if otherwise
 */
bool I3PhysicsModule::PutMCEvent(I3Frame& frame,I3MCEventPtr event,
				 const string& name)
{
  return I3FrameAccess<I3MCEvent>::Put(frame,event,name);
}

/**
 * checks to see if the frame has an event in it.
 * @return true if an event is present, false if not
 * @param frame the frame we want to check
 * @param name the name of the event in the frame.  Defaults to 'Physics'
 */
bool I3PhysicsModule::HasEvent(I3Frame& frame, const string& name )
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
I3Event& I3PhysicsModule::GetEvent(I3Frame& frame,const string& name )
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
bool I3PhysicsModule::PutEvent(I3Frame& frame,I3EventPtr event,const string& name)
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
bool I3PhysicsModule::HasMCEventHeader(I3Frame& frame,const string& name)
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
I3MCEventHeader& I3PhysicsModule::GetMCEventHeader(I3Frame& frame,
						   const string& name)
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
bool I3PhysicsModule::PutMCEventHeader(I3Frame& frame,
				       I3MCEventHeaderPtr header,
				       const string& name)
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
bool I3PhysicsModule::HasEventHeader(I3Frame& frame,const string& name)
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
I3EventHeader& I3PhysicsModule::GetEventHeader(I3Frame& frame,
					       const string& name)
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
bool I3PhysicsModule::PutEventHeader(I3Frame& frame,
				     I3EventHeaderPtr header,
				     const string& name)
{
  return I3FrameAccess<I3EventHeader>::Put(frame,header,name);
}

/**
 * Method to check for calibration in frame
 */
bool I3PhysicsModule::HasCalibration(I3Frame& frame, const string& name )
{
  return I3FrameAccess<I3Calibration>::Exists(frame,name);
}
    
/**
 * Method to put calibration into frame
 */
bool I3PhysicsModule::PutCalibration(I3Frame& frame,
				     I3CalibPtr calib,
				     const string& name )
{
  return I3FrameAccess<I3Calibration>::Put(frame,calib,name);
}
   
/**
 * Method to get calibration from frame
 */
I3Calibration& I3PhysicsModule::GetCalibration(I3Frame& frame, const string& name )
{
  return I3FrameAccess<I3Calibration>::Get(frame,name);
}
    

/**
 * Checks to see if a frame has a geometry in it
 * @param frame the frame we want to check
 * @param name the name of the geometry in the frame
 * @return true if the frame has a geometry, false if otherwise
 */
bool I3PhysicsModule::HasGeometry(I3Frame& frame,const string& name)
{
  return I3FrameAccess<I3Geometry>::Exists(frame,name);
}

/**
 * Gets the geometry out of the frame.  Just a helper method to simplify the
 * syntax
 * @return an I3Geometry that is in the frame
 * @param frame the frame that you want the geometry out of
 */
I3Geometry& I3PhysicsModule::GetGeometry(I3Frame& frame,const string& name)
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
bool I3PhysicsModule::PutGeometry(I3Frame& frame,
				  I3GeometryPtr geometry,
				  const string& name)
{
  return I3FrameAccess<I3Geometry>::Put(frame,geometry,name);
}

/*
 * Checks to see if a frame has a geometry headerin it
 * @param frame the frame we want to check
 * @param name the name of the geometry header in the frame
 * @return true if the frame has a geometry header, false if otherwise
 */
bool I3PhysicsModule::HasGeometryHeader(I3Frame& frame,const string& name)
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
I3GeometryHeader& I3PhysicsModule::GetGeometryHeader(I3Frame& frame, 
						     const string& name)
{
  return I3FrameAccess<I3GeometryHeader>::Get(frame,name);
}

/**
 * Puts a evemt header in the frame.  Just a helper method to 
 * simplify the syntax
 * @param frame the frame to put the geometry header into
 * @param header the geometry header to put into the frame
 * @param name the name of the header in the frame.  
 * Defaults to 'GeometryHeader'
 * @return true if it is successful, false if otherwise
 */
bool I3PhysicsModule::PutGeometryHeader(I3Frame& frame,
					I3GeometryHeaderPtr header,
					const string& name)
{
  return I3FrameAccess<I3GeometryHeader>::Put(frame,header,name);
}


/**
 * Does frame have a calibration header?
 */
bool I3PhysicsModule::HasCalibrationHeader(I3Frame& frame,const string& name)
{
  return I3FrameAccess<I3CalibrationHeader>::Exists(frame,name);
}

      
/**
 * Get the calibration header out of the frame.
 */
I3CalibrationHeader& I3PhysicsModule::GetCalibrationHeader(I3Frame& frame, 
							   const string& name)
{
  return I3FrameAccess<I3CalibrationHeader>::Get(frame,name);
}

/**
 * Put the calibration header into the frame
 */
bool I3PhysicsModule::PutCalibrationHeader(I3Frame& frame,
					   I3CalibrationHeaderPtr header,
					   const string& name)
{
  return I3FrameAccess<I3CalibrationHeader>::Put(frame,header,name);
}

/**
 * checks to see if the frame has a detector status in it.
 * @return true if an detector status is present, false if not
 * @param frame the frame we want to check
 * @param name the name of the detector status in the frame.  
 * Defaults to 'DetectorStatus'
 */
bool I3PhysicsModule::HasDetectorStatus(I3Frame& frame, 
					const string& name)
{
  return I3FrameAccess<I3DetectorStatus>::Exists(frame,name);
}

/**
 * Gets a  detector status out of a frame.  Just a helper method to 
 * simplify the
 * syntax.
 * @return an I3DetectorStatus that is in the frame
 * @param frame the frame that you want the detector status out of.
 * @param name the name of the detector status in the frame, 
 * defaults to "DetectorStatus"
 */
I3DetectorStatus& I3PhysicsModule::GetDetectorStatus(I3Frame& frame,
						     const string& name )
{
  return I3FrameAccess<I3DetectorStatus>::Get(frame,name);
}

/**
 * Puts a  detector status in the frame.  
 * Just a helper method to simplify the syntax
 * @param frame the frame to put the detector status into
 * @param detector status the detector status to put into the frame
 * @param name the name of the detector status in the frame.  
 * Defaults to 'DetectorStatus'
 * @return true if it is successful, false if otherwise
 */
bool I3PhysicsModule::PutDetectorStatus(I3Frame& frame,I3DetectorStatusPtr status,
					const string& name)
{
  return I3FrameAccess<I3DetectorStatus>::Put(frame,status,name);
}

/**
 * checks to see if the frame has a  detector status headerin it.
 * @return true if an detector status headeris present, false if not
 * @param frame the frame we want to check
 * @param name the name of the detector status header in the frame.  Defaults to
 * 'DetectorStatusHeader'
 */
bool I3PhysicsModule::HasDetectorStatusHeader(I3Frame& frame,
					      const string& name)
{
  return I3FrameAccess<I3DetectorStatusHeader>::Exists(frame,name);
}

/**
 * Gets an detector status header out of a frame.  Just a helper method 
 * to simplify syntax
 * @return the detector status header in the frame
 * @param frame the frame that you want the detector status header out of.
 * @param name the name of the detector status header in the frame.  Defaults to
 * 'DetectorStatusHeader'
 */
I3DetectorStatusHeader& I3PhysicsModule::GetDetectorStatusHeader(I3Frame& frame,
								 const string& name)
{
  return I3FrameAccess<I3DetectorStatusHeader>::Get(frame,name);
}

/**
 * Puts an detector status header in the frame.  Just a helper method to
 * simplify the syntax
 * @param frame the frame to put the detector status header into
 * @param header the detector status header to put into the frame
 * @param name the name of the header in the frame.
 * Defaults to 'DetectorStatusHeader'
 * @return true if it is successful, false if otherwise
 */
bool I3PhysicsModule::PutDetectorStatusHeader(I3Frame& frame,
					      I3DetectorStatusHeaderPtr header,
					      const string& name)
{
  return I3FrameAccess<I3DetectorStatusHeader>::Put(frame,header,name);
}


ClassImp(I3PhysicsModule);
