/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3CalculatorImpl.cxx,v 1.9 2004/11/29 19:37:14 dule Exp $

    @version $Revision: 1.9 $
    @date $Date: 2004/11/29 19:37:14 $
    @author

    @todo

*/
#include "phys-services/I3CalculatorImpl.h"
#include "dataclasses/I3Constants.h"
#include "dataclasses/I3Starting.h"
#include "dataclasses/I3Stopping.h"
#include "dataclasses/I3Contained.h"
#include <iostream>

using namespace std;
using namespace I3Constants;

//--------------------------------------------------------------
// Calculate distance between I3Position and Pos() of I3Track
Double_t I3CalculatorImpl::Distance(I3TrackPtr track, I3Position& pos)
{
  return pos.CalcDistance(track->GetPos());
}

//--------------------------------------------------------------
// Calculate distance between I3Position and Pos() of I3Cascade
Double_t I3CalculatorImpl::Distance(I3CascadePtr cascade, I3Position& pos)
{
  return pos.CalcDistance(cascade->GetPos());
}

//--------------------------------------------------------------
// Calculate distance to START position on track
Double_t I3CalculatorImpl::StartDistance(I3TrackPtr track, I3Position& pos)
{
  if (track->IsStarting()) {
    if (track->IsStopping()) {
     return pos.CalcDistance((roost::dynamic_pointer_cast<I3Contained>(track))->GetStartPos());
    } else {
     return pos.CalcDistance((roost::dynamic_pointer_cast<I3Starting>(track))->GetStartPos());
    }
  }
  return NAN;
}

//--------------------------------------------------------------
// Calculate distance to STOP position on track
Double_t I3CalculatorImpl::StopDistance(I3TrackPtr track, I3Position& pos)
{
  if (track->IsStopping()) {
    if (track->IsStarting()) {
      return pos.CalcDistance((roost::dynamic_pointer_cast<I3Contained>(track))->GetStopPos());
    } else {
      return pos.CalcDistance((roost::dynamic_pointer_cast<I3Stopping>(track))->GetStopPos());
    }
  }
  return NAN;
}

//--------------------------------------------------------------
// Calculate a position on track, which is a distance +/-dist 
// away from track.Pos().
I3Position I3CalculatorImpl::ShiftAlongTrack(I3TrackPtr track, Double_t dist)
{
  I3Position p;
  Double_t x,y,z;
  x = track->GetPos().GetX() 
    - dist*sin(track->GetDir().GetZenith())*cos(track->GetDir().GetAzimuth());
  y = track->GetPos().GetY() 
    - dist*sin(track->GetDir().GetZenith())*sin(track->GetDir().GetAzimuth());
  z = track->GetPos().GetZ() 
    - dist*cos(track->GetDir().GetZenith());
  p.SetPosition(x,y,z,I3Position::car);
  return p;
}

//--------------------------------------------------------------
// Calculate distance to CLOSEST APPROACH to track
void I3CalculatorImpl::CherenkovCalc(I3TrackPtr track,   // input
			       I3Position& pos,    // input
			       I3Position& appos,  // output 
			       Double_t& apdist,   // output
			       I3Position& chpos,  // output
			       Double_t& chtime,   // output
			       Double_t& chdist,   // output
			       Double_t IndexRef)   // input
{
  //--Only calculate if track has direction
  if (track->HasDirection()) {
    I3Position P(pos);   // position (P) of a DOM or whatnot
    Double_t theta = pi - track->GetZenith();
    Double_t phi = track->GetAzimuth() - pi;
    Double_t changle = acos(1/IndexRef); // calculate Cherenkov angle
    Double_t speed = c/IndexRef;

    //--Calculate position and distance of closest approach
    Double_t PT = P.CalcDistance(track->GetPos()); // T=track->Pos()
    P.ShiftCoordSystem(track->GetPos());
    P.RotateZ(-phi);
    P.RotateY(pi/2-theta);
    Double_t TA = P.GetX();
    Double_t PA = sqrt(PT*PT-TA*TA);

    //--Return position and distance of closest approach
    appos = ShiftAlongTrack(track,TA); // position A
    apdist = PA; // distance of closest approach

    //--Calculate Cherenkov photon... position on track and time of PMT hit
    Double_t CA = PA/tan(changle);
    Double_t CP = PA/sin(changle);
    Double_t TC = TA-CA;
    chpos = ShiftAlongTrack(track,TC); // origin of Cherenkov light (C)
    chtime = TC/c + CP/speed; //travel time:track Pos->I3Position
    chdist = CP; // distance between origin of Cherenkov light to I3Position
          // total photon time from T (on track) through C to P.
          // TC - particle's speed is c, but CP - photon's speed is c/n.

    //--Is point of closest approach (A) on track?
    //--Is Cherenkov origin point (C) on track?
    if (track->IsStarting()) 
      if (track->IsStopping()) {
      //-contained track...............................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = (roost::dynamic_pointer_cast<I3Contained>(track))
	    ->GetStartPos();
	  apdist = pos.CalcDistance(appos);
	} else if (TA>track->GetLength()) {
	  // if A is beyond STOPPING position
	  appos = (roost::dynamic_pointer_cast<I3Contained>(track))
	    ->GetStopPos();
	  apdist = pos.CalcDistance(appos);
	}
	if (TC<0) {
	  // if C is before STARTING position
	  chpos.NullPosition();
	  chtime = NAN;
	  chdist = NAN;
	} else if (TC>track->GetLength()) {
	  // if C is beyond STOPPING position
	  chpos.NullPosition();                                               
          chtime = NAN;
	  chdist = NAN;
	}
      } else {
      //-starting track................................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = (roost::dynamic_pointer_cast<I3Starting>(track))
	    ->GetStartPos();
	  apdist = pos.CalcDistance(appos);
	}
	if (TC<0) {
	  // if C is before STARTING position
	  chpos.NullPosition();
	  chtime = NAN;
	  chdist = NAN;
	}
      }
    else
      if (track->IsStopping()) {
      //-stopping track................................
	if (TA>0) {
	  // if A is beyond STOPPING position
	  appos = (roost::dynamic_pointer_cast<I3Stopping>(track))
	    ->GetStopPos();
	  apdist = pos.CalcDistance(appos);
	}
	if (TC>0) {
	  // if C is beyond STOPPING position
	  chpos.NullPosition();
	  chtime = NAN;
	  chdist = NAN;
	}
      } else {
      //-infitine track................................
      }

    //--Don't calculate if track does not have direction
  } else {
    cout <<"I3CalculatorImpl::CherenkovLight - Track has no direction. Not calculating.\n";
    appos.NullPosition();
    apdist=NAN;
    chpos.NullPosition();
    chtime=NAN;
  }
}

//--------------------------------------------------------------
// Is a given position on a track
Bool_t I3CalculatorImpl::IsOnTrack(I3TrackPtr track, 
				   I3Position& pos,
				   Double_t Precision)
{
  I3Position appos,chpos;
  Double_t apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  if (apdist<=Precision) return kTRUE;
  else return kFALSE;
}

//--------------------------------------------------------------
// Return the distance of closets approach from I3Track to I3Position
Double_t I3CalculatorImpl::ClosestApproachDistance(I3TrackPtr track,
						   I3Position& pos)
{
  I3Position appos,chpos;
  Double_t apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  return apdist;
}

//--------------------------------------------------------------
// Return the time for Cherenkov photon from I3Track to I3Position
Double_t I3CalculatorImpl::CherenkovTime(I3TrackPtr track,
					 I3Position& pos,
					 Double_t IndexRef)
{
  I3Position appos,chpos;
  Double_t apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist,IndexRef);
  return chtime;
}

//--------------------------------------------------------------
// Return the time for Cherenkov photon from I3Track to I3Position
Double_t I3CalculatorImpl::CherenkovDistance(I3TrackPtr track,
					     I3Position& pos)
{
  I3Position appos,chpos;
  Double_t apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  return chdist;
}

//--------------------------------------------------------------
// Return angle between incident Cherenkov direction onto the DOM
// and the -z axis, at I3Position (DOM)
Double_t I3CalculatorImpl::CherenkovAngle(I3TrackPtr track,
					  I3Position& pos,
					  I3OMGeo::EOrientation orient)
{
  I3Position appos,chpos;
  Double_t apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  I3Position P(pos);             // position (P) of a DOM or whatnot
  P.ShiftCoordSystem(chpos);     // get coordinates when C is origin.
  Double_t angle = P.GetTheta(); // return theta of new P
  if (orient==I3OMGeo::Up) { angle = pi-angle; } // in case OM points UP
  return angle;
}

//--------------------------------------------------------------
// Return the time for photon from I3Cascade to I3Position
Double_t I3CalculatorImpl::CascadeTime(I3CascadePtr cascade,
				       I3Position& pos,
				       Double_t IndexRef)
{
  Double_t speed=c/IndexRef;
  return pos.CalcDistance(cascade->GetPos())/speed;
}

//--------------------------------------------------------------
// Return the distance from I3Cascade to I3Position
Double_t I3CalculatorImpl::CascadeDistance(I3CascadePtr cascade,
					   I3Position& pos)
{
  return pos.CalcDistance(cascade->GetPos());
}

//--------------------------------------------------------------
// Return the angle between two tracks
Double_t I3CalculatorImpl::AngleDiff(I3TrackPtr track1,
				     I3TrackPtr track2)
{
  I3Direction dir1(track1->GetDir());
  I3Direction dir2(track2->GetDir());
  dir1.RotateZ(-dir2.CalcPhi());
  dir1.RotateY(-dir2.CalcTheta());
  Double_t theta = dir1.CalcTheta();
  return theta;
}

//--------------------------------------------------------------
