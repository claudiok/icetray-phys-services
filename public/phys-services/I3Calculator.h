/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3Calculator.h,v 1.3 2004/07/30 19:55:07 dule Exp $
 *
 * @file I3TrackImpl.h
 * @version $Revision: 1.3 $
 * @date $Date: 2004/07/30 19:55:07 $
 * @author pretz
 */
#ifndef I3CALCULATOR_H
#define I3CALCULATOR_H

#include <TObject.h>
#include <cmath>
#include "dataclasses/I3Track.h"
#include "dataclasses/I3Cascade.h"
#include "dataclasses/I3Units.h"

#include <iostream>

/**
 * @brief A class for the service that calculates various distances 
 * between a track and a position.
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
  virtual Double_t Distance(I3TrackPtr track, I3Position& pos) = 0;
  
  /**
   * Distance between position P and position Pos() of cascade
   */
  virtual Double_t Distance(I3CascadePtr cascade, I3Position& pos) = 0;
  
  /**
   * Distance between position P and start position on track
   */
  virtual Double_t StartDistance(I3TrackPtr track, I3Position& pos) =0;
  
  /**
   * Distance between position P and stop position on track
   */
  virtual Double_t StopDistance(I3TrackPtr track, I3Position& pos) =0;
  
  /**
   * Calculate a position on track, which is a distance 'dist'
   * away from track.Pos().
   */
  virtual I3Position ShiftAlongTrack(I3TrackPtr track, 
				     Double_t dist) = 0;
  
  /**
   * Check is Position is on Track within the given Precision.
   * Default Precision is 10cm, but can be given by user.
   * 
   * @todo IsOnTrack uses CherenkovCalc for calculating "distance of closest
   * approach".  This method is not the most efficient, but makes the code much
   * simpler.  If processing time becomes an issue, we can make these routines 
   * more efficient.
   */
  virtual Bool_t IsOnTrack(I3TrackPtr track, 
			   I3Position& pos,
			   Double_t Precision=0.1*I3Units::meter) = 0;
   
  /**
   * Output distance of closest approach from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  virtual Double_t ClosestApproachDistance(I3TrackPtr track,
					   I3Position& pos) = 0;


 /**
   * Output time of arrival of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   * @param IndexRef input Index of Refraction with default value of 1.31
   */
  virtual Double_t CherenkovTime(I3TrackPtr track,
	           		 I3Position& pos,
				 Double_t IndexRef=1.31) = 0;

 /**
   * Output distance from origin of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  virtual Double_t CherenkovDistance(I3TrackPtr track,
				     I3Position& pos) = 0;

 /**
   * Output angle between Cherenkov path and the z-axis of the I3Position (DOM)
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  virtual Double_t CherenkovAngle(I3TrackPtr track,
				  I3Position& pos) = 0;

 /**
   * Output time of arrival of Cherenkov light from I3Cascade to I3Position.
   * 
   * @param cascade input cascade position
   * @param pos input position
   * @param IndexRef input Index of Refraction with default value of 1.31
   */
  virtual Double_t CascadeTime(I3CascadePtr cascade,
			       I3Position& pos,
			       Double_t IndexRef=1.31) = 0;

 /**
   * Output distance from center of I3Cascade to I3Position.
   * 
   * @param cascade input cascade position
   * @param pos input position
   */
  virtual Double_t CascadeDistance(I3CascadePtr cascade,
				   I3Position& pos) = 0;


 protected:

  // ROOT macro
  ClassDef(I3Calculator,1);
};


#endif
