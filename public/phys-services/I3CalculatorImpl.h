/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3CalculatorImpl.h,v 1.3 2004/07/30 19:55:07 dule Exp $
 *
 * @file I3CalculatorImpl.h
 * @version $Revision: 1.3 $
 * @date $Date: 2004/07/30 19:55:07 $
 * @author dule
 */
#ifndef I3CALCULATORIMPL_H
#define I3CALCULATORIMPL_H

#include <TObject.h>
#include <cmath>
#include "dataclasses/I3Track.h"
#include "dataclasses/I3Units.h"
#include "phys-services/I3Calculator.h"

#include <iostream>

/**
 * @brief A class for the service that calculates various distances 
 * between a track and a position.
 *
 * This class is intended to be a service, separate from dataclasses.
 * 
 * @todo Migrate this whole class out of dataclasses and into services.
 */
class I3CalculatorImpl : public I3Calculator
{

 public:
  /**
   * constructor
   */
  I3CalculatorImpl() {};

  /**
   * destructor
   */
  virtual ~I3CalculatorImpl() {};

  /**
   * Distance between position P and position Pos() on track
   */
  Double_t Distance(I3TrackPtr track, I3Position& pos);

  /**
   * Distance between position P and position Pos() of cascade
   */
  Double_t Distance(I3CascadePtr cascade, I3Position& pos);

  /**
   * Distance between position P and start position on track
   */
  Double_t StartDistance(I3TrackPtr track, I3Position& pos);

  /**
   * Distance between position P and stop position on track
   */
  Double_t StopDistance(I3TrackPtr track, I3Position& pos);

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
		     Double_t& apdist,
		     I3Position& chpos,
		     Double_t& chtime,
		     Double_t& chdist,
		     Double_t IndexRef=1.31);

  /**
   * Calculate a position on track, which is a distance 'dist'
   * away from track.Pos().
   */
  I3Position ShiftAlongTrack(I3TrackPtr track, 
			     Double_t dist);

  /**
   * Check is Position is on Track within the given Precision.
   * Default Precision is 10cm, but can be given by user.
   * 
   * @todo IsOnTrack uses CherenkovCalc for calculating "distance of closest
   * approach".  This method is not the most efficient, but makes the code much
   * simpler.  If processing time becomes an issue, we can make these routines 
   * more efficient.
   */
  Bool_t IsOnTrack(I3TrackPtr track, 
		   I3Position& pos,
		   Double_t Precision=0.1*I3Units::meter);

  /**
   * Output distance of closest approach from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  Double_t ClosestApproachDistance(I3TrackPtr track,
				   I3Position& pos);

  /**
   * Output time of arrival of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  Double_t CherenkovTime(I3TrackPtr track,
			 I3Position& pos,
			 Double_t IndexRef=1.31);

 /**
   * Output distance from origin of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  Double_t CherenkovDistance(I3TrackPtr track,
			     I3Position& pos);

 /**
   * Output angle between Cherenkov path and the z-axis of the I3Position (DOM)
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  Double_t CherenkovAngle(I3TrackPtr track,
			  I3Position& pos);

  /**
   * Output time of arrival of Cherenkov light from I3Cascade to I3Position.
   * 
   * @param cascade input cascade
   * @param pos input position
   * @param IndexRef input index of refraction (default=1.31).
   */
  Double_t CascadeTime(I3CascadePtr cascade,
		       I3Position& pos,
		       Double_t IndexRef=1.31);

 /**
   * Output distance from center of I3Cascade to I3Position.
   * 
   * @param cascade input cascade position
   * @param pos input position
   */
  Double_t CascadeDistance(I3CascadePtr cascade,
			   I3Position& pos);


 protected:

  // ROOT macro
  ClassDef(I3CalculatorImpl,1);
};


#endif
