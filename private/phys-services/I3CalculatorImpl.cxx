/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3CalculatorImpl.cxx,v 1.9.4.1 2005/03/11 15:09:51 dule Exp $

    @version $Revision: 1.9.4.1 $
    @date $Date: 2005/03/11 15:09:51 $
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
double I3CalculatorImpl::Distance(I3TrackPtr track, I3Position& pos)
{
  return pos.CalcDistance(track->GetPos());
}

//--------------------------------------------------------------
// Calculate distance between I3Position and Pos() of I3Cascade
double I3CalculatorImpl::Distance(I3CascadePtr cascade, I3Position& pos)
{
  return pos.CalcDistance(cascade->GetPos());
}

//--------------------------------------------------------------
// Calculate distance between Pos() of two I3Cascades
double I3CalculatorImpl::Distance(I3CascadePtr casc1, I3CascadePtr casc2)
{
  return casc1->GetPos().CalcDistance(casc2->GetPos());
}

//--------------------------------------------------------------
// Calculate distance to START position on track
double I3CalculatorImpl::StartDistance(I3TrackPtr track, I3Position& pos)
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
double I3CalculatorImpl::StopDistance(I3TrackPtr track, I3Position& pos)
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
I3Position I3CalculatorImpl::ShiftAlongTrack(I3TrackPtr track, double dist)
{
  I3Position p;
  double x,y,z;
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
			       double& apdist,   // output
			       I3Position& chpos,  // output
			       double& chtime,   // output
			       double& chdist,   // output
			       double IndexRef)   // input
{
  //--Only calculate if track has direction
  if (track->HasDirection()) {
    I3Position P(pos);   // position (P) of a DOM or whatnot
    double theta = pi - track->GetZenith();
    double phi = track->GetAzimuth() - pi;
    double changle = acos(1/IndexRef); // calculate Cherenkov angle
    double speed = c/IndexRef;

    //--Calculate position and distance of closest approach
    double PT = P.CalcDistance(track->GetPos()); // T=track->Pos()
    P.ShiftCoordSystem(track->GetPos());
    P.RotateZ(-phi);
    P.RotateY(pi/2-theta);
    double TA = P.GetX();
    double PA = sqrt(PT*PT-TA*TA);

    //--Return position and distance of closest approach
    appos = ShiftAlongTrack(track,TA); // position A
    apdist = PA; // distance of closest approach

    //--Calculate Cherenkov photon... position on track and time of PMT hit
    double CA = PA/tan(changle);
    double CP = PA/sin(changle);
    double TC = TA-CA;
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
Bool_t I3CalculatorImpl::IsOnTrack(I3TrackPtr track, I3Position& pos,
											  double Precision)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  if (apdist<=Precision) return kTRUE;
  else return kFALSE;
}

//--------------------------------------------------------------
// Return the distance of closets approach from I3Track to I3Position
double I3CalculatorImpl::ClosestApproachDistance(I3TrackPtr track,
																 I3Position& pos)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  return apdist;
}

//--------------------------------------------------------------
// Return the time for Cherenkov photon from I3Track to I3Position
double I3CalculatorImpl::CherenkovTime(I3TrackPtr track, I3Position& pos,
													double IndexRef)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist,IndexRef);
  return chtime;
}

//--------------------------------------------------------------
// Return the time for Cherenkov photon from I3Track to I3Position
double I3CalculatorImpl::CherenkovDistance(I3TrackPtr track, I3Position& pos)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  return chdist;
}

//--------------------------------------------------------------
// Return angle between incident Cherenkov direction onto the DOM
// and the -z axis, at I3Position (DOM)
double I3CalculatorImpl::CherenkovAngle(I3TrackPtr track, I3Position& pos,
													 I3OMGeo::EOrientation orient)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  I3Position P(pos);             // position (P) of a DOM or whatnot
  P.ShiftCoordSystem(chpos);     // get coordinates when C is origin.
  double angle = P.GetTheta(); // return theta of new P
  if (orient==I3OMGeo::Up) { angle = pi-angle; } // in case OM points UP
  return angle;
}

//--------------------------------------------------------------
// Return the time for photon from I3Cascade to I3Position
double I3CalculatorImpl::CascadeTime(I3CascadePtr cascade, I3Position& pos,
												 double IndexRef)
{
  double speed=c/IndexRef;
  return pos.CalcDistance(cascade->GetPos())/speed;
}

//--------------------------------------------------------------
// Return the distance from I3Cascade to I3Position
double I3CalculatorImpl::CascadeDistance(I3CascadePtr cascade, I3Position& pos)
{
  return pos.CalcDistance(cascade->GetPos());
}

//--------------------------------------------------------------
// Return the angle between two tracks
double I3CalculatorImpl::AngleDiff(I3TrackPtr track1, I3TrackPtr track2)
{
  I3Direction dir1(track1->GetDir());
  I3Direction dir2(track2->GetDir());
  dir1.RotateZ(-dir2.CalcPhi());
  dir1.RotateY(-dir2.CalcTheta());
  double theta = dir1.CalcTheta();
  return theta;
}

//--------------------------------------------------------------
// Return the number of direct hits
int I3CalculatorImpl::Ndir(I3TrackPtr track, I3Position& pos, double time)
{
	return 1;
}

//--------------------------------------------------------------
