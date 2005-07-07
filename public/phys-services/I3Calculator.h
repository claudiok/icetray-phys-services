/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3TrackImpl.h
 * @version $Revision: 1.16 $
 * @date $Date$
 * @author pretz
 */
#ifndef I3CALCULATOR_H
#define I3CALCULATOR_H

#include <TObject.h>
#include <cmath>
#include "dataclasses/I3Track.h"
#include "dataclasses/I3Cascade.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/I3Constants.h"
#include "dataclasses/I3OMGeo.h"

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
namespace I3Calculator
{

  /**
   * Distance between position P and closest approach position on track
   * Input a position 'pos' and a track 'track', and output 
   * position of closest approach: 'appos'
   * distance of closest approach: 'apdist'
   * position of origin of Cherenkov photon: 'chpos'
   * time of photon from track Pos() until the Position (pos): 'chtime'
   *
   * @param track input I3Track
   * @param pos input I3Position
   * @param appos output I3Position of closest approach
   * @param apdist output closest approach distance
   * @param chpos output I3Position of origin of Cherenkov light to the input
   * I3Position
   * @param chdist output time of Cherenkov light from position Pos() of the
   * input I3Track to the input I3Position
   * @param IndexRef input index of refraction (default=1.31)
   *
   * @todo Right now, CherenkovCalc calculates "closest approach" AND 
   * "cherenkov distances".  This is good for simplicity and non-repetitiveness
   * of the code, but it is not the most efficient.  If processing time becomes
   * an issue, we can make these things more efficient at the expence of
   * complicating and repeating the code.
   */
  void CherenkovCalc(I3TrackPtr track,
		     I3Position& pos,
		     I3Position& appos,
		     double& apdist,
		     I3Position& chpos,
		     double& chtime,
		     double& chdist,
		     double IndexRef=I3Constants::n_ice);

  /**
   * Return a position on track, which is a distance 'dist' away 
   * from track.Pos().
   * 'dist' can be both positive and negative...
   */
  I3Position ShiftAlongTrack(I3TrackPtr track, 
			     double dist);
  
  /**
   * Check is Position is on Track within the given Precision.
   * Default Precision is 10cm, but can be given by user.
   * 
   * @todo IsOnTrack uses CherenkovCalc for calculating "distance of closest
   * approach".  This method is not the most efficient, but makes the code much
   * simpler.  If processing time becomes an issue, we can make these routines 
   * more efficient.
   */
  bool IsOnTrack(I3TrackPtr track, 
		 I3Position& pos,
		 double Precision=0.1*I3Units::meter);
   
  /**
   * Output distance of closest approach from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   */
  double ClosestApproachDistance(I3TrackPtr track,
				 I3Position& pos);
   
  /**
   * Output position of closest approach from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   */
  I3Position ClosestApproachPosition(I3TrackPtr track,
				     I3Position& pos);

 /**
   * Output distance from origin of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   */
  double CherenkovDistance(I3TrackPtr track,
			   I3Position& pos);

 /**
   * Output time of arrival of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   */
  double CherenkovTime(I3TrackPtr track,
		       I3Position& pos,
		       double IndexRef=I3Constants::n_ice);

 /**
   * Return angle between Cherenkov path and the z-axis of the I3Position (DOM)
   * This method simply uses CherenkovCalc for the calculation.
   */
  double CherenkovAngle(I3TrackPtr track,
			I3Position& pos,
			I3OMGeo::EOrientation orient=I3OMGeo::Down);

  /**
   * Return distance between I3Position and position Pos() of I3Cascade
   */
  double CascadeDistance(I3CascadePtr cascade, 
			 I3Position& pos);
  
  /**
   * Return distance between position Pos() of two I3Cascades
   */
  double CascadeDistance(I3CascadePtr casc1, 
			 I3CascadePtr casc2);
  
 /**
   * Return time of arrival of Cherenkov light from I3Cascade to I3Position.
   */
  double CascadeTime(I3CascadePtr cascade,
		     I3Position& pos,
		     double IndexRef=I3Constants::n_ice);

  /**
   * Return the spatial angle between two tracks
   */
  double AngleDiff(I3TrackPtr track1,
		   I3TrackPtr track2);

};

#endif
