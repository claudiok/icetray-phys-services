/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3Calculator.h
 * @version $Revision: 1.16 $
 * @date $Date$
 * @author pretz
 */
#ifndef I3CALCULATOR_H
#define I3CALCULATOR_H

#include <cmath>
#include "dataclasses/physics/I3BasicTrack.h"
class I3Cascade;
#include "dataclasses/I3Units.h"
#include "dataclasses/I3Constants.h"
#include "dataclasses/geometry/I3OMGeo.h"

using namespace I3Units;

/**
 * @brief This is a namespace, which provides a collection of stand-alone 
 * functions that calculate various quantites relating a track, a cascade, 
 * and an OM position.  These quantities include a various distances between 
 * two points, angle difference between two directions, time of travel of 
 * light...
 *
 * Many of the methods are wrapper methods, which are designed for ease of 
 * use,  and internally call the main calculation methods.  These can be used 
 * for simplicity.  The expert user can just use the main calculation 
 * methods/functions.
 */
namespace I3Calculator
{
  /**
   * Returns a position on the input track ('track'), which is a distance 
   * 'dist' away from the track's nominal position.  If 'dist' is positive, 
   * the position is shifted by 'dist' in the direction of the track; 
   * a negative 'dist' will shift the position in the opposite direction.
   */
  I3Position ShiftAlongTrack(const I3BasicTrack& track, 
			     const double dist);
  
  /**
   * The main calculation function, which calculates in one step the relevant 
   * quantities that relate a track to an OM position.  If you are interested
   * in all of these quantities (see Output Parameters), use this function.
   * 
   * 
   * INPUT:
   * @param track -- Smart pointer to a track.
   *
   * @param position -- Position of an OM.
   *
   * @param IndexRef -- Index of refraction (default=1.31).
   *
   * @param orient -- Orientation of the OM.
   *
   *
   * OUTPUT:
   * @param appos -- Position of the point of closest 
   * approach of the track to the input OM position ('position').  This is 
   * simply the position on the track which is closest to the input position.  
   * In case of a finite track, if this theoretical position is beyond the 
   * end of the track, then either the start or stop position of the track
   * is returned, which ever one is closer to 'position'.
   *
   * @param apdist -- Closest approach distance.  This is 
   * the distance between the input OM ('position') and the calculated point 
   * of closest approach ('appos').
   *
   * @param chpos -- Position on the track, which is the
   * origin of Cherenkov light that arrives at the input OM position
   * ('position').  If no Cherenkov light originating from the input track
   * can arrive at the input OM position, 'chpos' will be a null I3Position.
   *
   * @param chtime -- Time between the track's nominal time 
   * and the time of the arrival of Cherenkov light at the input OM position.  
   * This 'chtime' includes the time (which could be negative) for the 
   * particle to travel (at speed c) from the track's nominal time to the 
   * point of origin of Cherenkov light ('chpos') PLUS the time (which is 
   * always positive) it takes the Cherenkov light to travel (at speed c/n) 
   * from its point of origin to the input OM position.  If no Cherenkov 
   * light originating from the input track can arrive at the input OM 
   * position, 'chtime' will be NAN.
   *
   * @param chdist -- Distance between the point of origin 
   * of Cherenkov light and the input OM position.
   * 
   * @param chapangle -- Angle between the path of Cherenkov 
   * light originating from the input track ('track') and the z-axis of the 
   * input OM position ('position').
   * 
   *
   * @todo Currently, CherenkovCalc calculates "closest approach" AND 
   * "cherenkov distances".  This is good for simplicity and non-repetitiveness
   * of the code, but it is not the most efficient.  If processing time becomes
   * an issue, we can make these things more efficient at the expence of
   * complicating and repeating the code.
   */
  void CherenkovCalc(const I3BasicTrack& track,
		     const I3Position& position,
		     I3Position& appos,
		     double& apdist,
		     I3Position& chpos,
		     double& chtime,
		     double& chdist,
		     double& changle,
		     const double IndexRef=I3Constants::n_ice,
		     const I3OMGeo::Orientation orient=I3OMGeo::Down);

  /**
   * Check if the input position ('position') lies on the input track 
   * ('track') within the given Precision.  The default Precision is 10cm.
   * 
   * @todo IsOnTrack uses CherenkovCalc for calculating "distance of closest
   * approach".  This method is not the most efficient, but makes the code much
   * simpler.  If processing time becomes an issue, we can make these routines 
   * more efficient.
   */
  bool IsOnTrack(const I3BasicTrack& track, 
		 const I3Position& position,
		 const double Precision=0.1*I3Units::meter);

  /**
   * A convenience function that calls CherenkovCalc() and returns the 
   * position of closest approach from (an I3Position) between the input 
   * track and OM position.  If you are interested in more than one quantity
   * from CherenkovCalc(), use the CherenkovCalc() function directly, in
   * order to save multiple calls to the function.
   */
  I3Position ClosestApproachPosition(const I3BasicTrack& track,
				     const I3Position& position);

  /**
   * A convenience function that calls CherenkovCalc() and returns the 
   * distance of closest approach (a double) between the input track and 
   * OM position.  If you are interested in more than one quantity
   * from CherenkovCalc(), use the CherenkovCalc() function directly, in
   * order to save multiple calls to the function.
   */
  double ClosestApproachDistance(const I3BasicTrack& track,
				 const I3Position& position);

 /**
   * A convenience function that calls CherenkovCalc() and returns the 
   * position on the input track, which is the point of origin of Cherenkov 
   * light which arrives at the input OM position.  If no Cherenkov light 
   * from the track can reach the OM, the function returns a null I3Position.
   * If you are interested in more than one quantity from CherenkovCalc(), 
   * use the CherenkovCalc() function directly, in order to save multiple 
   * calls to the function.
   */
  I3Position CherenkovPosition(const I3BasicTrack& track,
			       const I3Position& position);

 /**
   * A convenience function that calls CherenkovCalc() and returns the time
   * between the track's nominal time and the time of arrival of Cherenkov 
   * light at the input OM position.  If no Cherenkov light from the 
   * track can reach the OM, the function returns a NAN.  If you are 
   * interested in more than one quantity from CherenkovCalc(), use the 
   * CherenkovCalc() function directly, in order to save multiple calls to 
   * the function.
   */
  double CherenkovTime(const I3BasicTrack& track,
		       const I3Position& position,
		       const double IndexRef=I3Constants::n_ice);

 /**
   * A convenience function that calls CherenkovCalc() and returns the 
   * distance from origin of Cherenkov light on the input track to the input 
   * OM position.  If you are interested in more than one quantity
   * from CherenkovCalc(), use the CherenkovCalc() function directly, in
   * order to save multiple calls to the function.
   */
  double CherenkovDistance(const I3BasicTrack& track,
			   const I3Position& position);

 /**
   * A convenience function that calls CherenkovCalc() and returns the
   * angle between the path of Cherenkov light from the input track and the 
   * z-axis of the input OM position.  An optional input is the orientation 
   * of the OM (default = Down).  If you are interested in more than one 
   * quantity from CherenkovCalc(), use the CherenkovCalc() function 
   * directly, in order to save multiple calls to the function.
   */
  double CherenkovApproachAngle(const I3BasicTrack& track,
			    const I3Position& position,
			    const I3OMGeo::Orientation orient=I3OMGeo::Down);

 /**
   * A convenience function that calls I3Position::CalcDistance() to calculate
   * the time it takes Cherenkov light to travel between an input cascade and
   * an OM position.  The index of refraction can be set by the user.
   */
#if 0
  double CherenkovTime(const I3Cascade& cascade,
		       const I3Position& position,
		       const double IndexRef=I3Constants::n_ice);

  /**
   * A convenience function that calls I3Position::CalcDistance() to calculate
   * the distance between an input cascade and an OM position.   
   */
  double CherenkovDistance(const I3Cascade& cascade, 
			   const I3Position& position);
#endif

  /**
   * A convenience function that calls CherenkovTime() and calculates the time 
   * residual between a hit and a track.
   * A time residual is defined as the difference between the measured hit time
   * and the expected time of arrival of a photon from the track.
   */
  double TimeResidual(const I3BasicTrack& track, 
		      const I3Position& hitpos, 
		      const double hittime,
		      const double IndexRef=I3Constants::n_ice);

  /**
   * A convenience function that calls CherenkovTime() and calculates the time 
   * residual between a hit and a cascade.
   * A time residual is defined as the difference between the measured hit time
   * and the expected time of arrival of a photon from the cascade.
   */
#if 0
  double TimeResidual(const I3Cascade& cascade, 
		      const I3Position& hitpos, 
		      const double hittime,
		      const double IndexRef=I3Constants::n_ice);
#endif

  /**
   * Returns the spatial angle between two input tracks.
   */
  double Angle(const I3BasicTrack& track1,
	       const I3BasicTrack& track2);

  /**
   * Returns the distance between two input cascades.
   */
#if 0
  double Distance(const I3Cascade& casc1, 
		  const I3Cascade& casc2);
#endif

  /**
   * Transform the input position into the coordinate system of the input 
   * track.  Effectively, the track is now in the z-dir.
   */
  I3Position InTrackSystem(const I3Direction& direction, 
			   const I3Position& pos);

  /**
   * Transform the input position into the coordinate system of the input 
   * track.  Effectively, the track is now in the z-dir.
   */
  I3Direction InTrackSystem(const I3Direction& direction, 
			    const I3Direction& dir);

  /**
   * Convenience function overload that extracts the direction out of a track
   * and then calls the regular InTrackSystem().
   */
  I3Position InTrackSystem(const I3BasicTrack& track, 
			   const I3Position& pos);

  /**
   * Convenience function overload that extracts the direction out of a track
   * and then calls the regular InTrackSystem().
   */
  I3Direction InTrackSystem(const I3BasicTrack& track, 
			    const I3Direction& dir);

  /**
   * Transform the input position out of the coordinate system of the input 
   * track.  Effectively, the track is now in its original direction.
   */
  I3Position InNominalSystem(const I3Direction& direction, 
			     const I3Position& pos);

  /**
   * Transform the input position out of the coordinate system of the input 
   * track.  Effectively, the track is now in its original direction.
   */
  I3Direction InNominalSystem(const I3Direction& direction, 
			      const I3Direction& dir);

  /**
   * Convenience function overload that extracts the direction out of a track
   * and then calls the regular InNominalSystem().
   */
  I3Position InNominalSystem(const I3BasicTrack& track, 
			     const I3Position& pos);

  /**
   * Convenience function overload that extracts the direction out of a track
   * and then calls the regular InNominalSystem().
   */
  I3Direction InNominalSystem(const I3BasicTrack& track, 
			      const I3Direction& dir);

};

#endif
