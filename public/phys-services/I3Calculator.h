/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3Calculator.h,v 1.1 2004/06/24 14:27:55 pretz Exp $
 *
 * @file I3TrackImpl.h
 * @version $Revision: 1.1 $
 * @date $Date: 2004/06/24 14:27:55 $
 * @author pretz
 */
#ifndef I3CALCULATOR_H
#define I3CALCULATOR_H

#include <TObject.h>
#include <cmath>
#include "dataclasses/I3Track.h"
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
   * Output time of arrival of Cherenkov light from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   * @param ChAngle input Cherenkov angle with a default value of 41 deg.
   */
  virtual Double_t CherenkovTime(I3TrackPtr track,
	           		 I3Position& pos,
				 Double_t ChAngle=41*I3Units::degree) = 0;
  
  /**
   * Output distance of closest approach from I3Track to I3Position.
   * This method simply uses CherenkovCalc for the calculation.
   * 
   * @param track input track
   * @param pos input position
   */
  virtual Double_t ClosestApproachDistance(I3TrackPtr track,
					   I3Position& pos) = 0;


 protected:

  // ROOT macro
  ClassDef(I3Calculator,1);
};


#endif
