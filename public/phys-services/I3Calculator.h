/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3Calculator.h,v 1.14 2005/04/12 18:43:58 pretz Exp $
 *
 * @file I3TrackImpl.h
 * @version $Revision: 1.14 $
 * @date $Date: 2005/04/12 18:43:58 $
 * @author pretz
 */
#ifndef I3CALCULATOR_H
#define I3CALCULATOR_H

#include <TObject.h>
#include <cmath>
#include "dataclasses/I3Track.h"
#include "dataclasses/I3Cascade.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/I3OMGeo.h"
#include "dataclasses/I3OMResponseMap.h"
#include "dataclasses/I3Geometry.h"

using namespace I3Units;

/**
 * @brief A class for the service that calculates various distances 
 * between a track and a position.
 * One must create an I3Calculator object to do any kind of calculation:
 * I3Calculator calc;
 * calc.CherenkovTime(...);
 *
 * This class is intended to be a service, separate from dataclasses.
 * 
 */
class I3Calculator
{

 public:
  /**
   * constructor
   */
  I3Calculator() {};

  /**
   * destructor
   */
  virtual ~I3Calculator() {};

  /**
   * Distance between position P and position Pos() on track
   */
  virtual double Distance(I3TrackPtr track, 
								  I3Position& pos) = 0;
  
  /**
   * Distance between position P and position Pos() of cascade
   */
  virtual double Distance(I3CascadePtr cascade, 
								  I3Position& pos) = 0;
  
  /**
   * Distance between position Pos() of two particles
   */
  virtual double Distance(I3CascadePtr casc1, 
								  I3CascadePtr casc2) = 0;
  
  /**
   * Distance between position P and start position on track
   */
  virtual double StartDistance(I3TrackPtr track, 
										 I3Position& pos) =0;
  
  /**
   * Distance between position P and stop position on track
   */
  virtual double StopDistance(I3TrackPtr track, 
										I3Position& pos) =0;
  
  /**
   * Calculate a position on track, which is a distance 'dist'
   * away from track.Pos().
   */
  virtual I3Position ShiftAlongTrack(I3TrackPtr track, 
												 double dist) = 0;
  
  /**
   * Check is Position is on Track within the given Precision.
   * Default Precision is 10cm, but can be given by user.
   * 
   * @todo IsOnTrack uses CherenkovCalc for calculating "distance of closest
   * approach".  This method is not the most efficient, but makes the code much
   * simpler.  If processing time becomes an issue, we can make these routines 
   * more efficient.
   */
  virtual bool IsOnTrack(I3TrackPtr track, 
									I3Position& pos,
									double Precision=0.1*I3Units::meter) = 0;
   
  /**
   * Output distance of closest approach from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  virtual double ClosestApproachDistance(I3TrackPtr track,
													  I3Position& pos) = 0;


 /**
   * Output time of arrival of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   * @param IndexRef input Index of Refraction with default value of 1.31
   */
  virtual double CherenkovTime(I3TrackPtr track,
										 I3Position& pos,
										 double IndexRef=1.31) = 0;

 /**
   * Output distance from origin of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  virtual double CherenkovDistance(I3TrackPtr track,
											  I3Position& pos) = 0;

 /**
   * Output angle between Cherenkov path and the z-axis of the I3Position (DOM)
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  virtual double CherenkovAngle(I3TrackPtr track,
										  I3Position& pos,
										 I3OMGeo::EOrientation orient=I3OMGeo::Down) = 0;

 /**
   * Output time of arrival of Cherenkov light from I3Cascade to I3Position.
   * 
   * @param cascade input cascade position
   * @param pos input position
   * @param IndexRef input Index of Refraction with default value of 1.31
   */
  virtual double CascadeTime(I3CascadePtr cascade,
									  I3Position& pos,
									  double IndexRef=1.31) = 0;

 /**
   * Output distance from center of I3Cascade to I3Position.
   * 
   * @param cascade input cascade position
   * @param pos input position
    */
  virtual double CascadeDistance(I3CascadePtr cascade,
											I3Position& pos) = 0;

  /**
   * Output the 3D angle between two tracks
   *
   * @param track1 first track
   * @param track2 second track
   */
  virtual double AngleDiff(I3TrackPtr track1,
									I3TrackPtr track2) = 0;

  /**
	* Calculate the number of direct hits from a given track.
	* The moethod counts the hits with small time residuals (between t1, t2)
	* (t1~=-15ns, t2~=25ns..150ns)
	*/
  virtual double Ndir(I3TrackPtr track, 
						 I3OMResponseMap& ommap, 
						 I3Geometry& geom, 
						 string hitseries = "Hits",
						 double t1 = -15*ns, 
						 double t2 = +25*ns) = 0;

  /**
   * Gives a default name for this service.  Defaults to "Calculator"
   */
  static const char* DefaultName(){return "Calculator";}
  
 protected:

  // ROOT macro
  ClassDef(I3Calculator,1);
};

typedef shared_ptr<I3Calculator> I3CalculatorPtr;


#endif
