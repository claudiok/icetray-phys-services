/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3CalculatorImpl.cxx,v 1.3 2004/07/13 14:23:57 pretz Exp $

    @version $Revision: 1.3 $
    @date $Date: 2004/07/13 14:23:57 $
    @author

    @todo

*/
#include "phys-services/I3CalculatorImpl.h"
#include "dataclasses/I3Constants.h"
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
  if (track->IsStarting() || track->IsContained()) {
    return pos.CalcDistance(track->GetStartPos());
  }
  return NAN;
}

//--------------------------------------------------------------
// Calculate distance to STOP position on track
Double_t I3CalculatorImpl::StopDistance(I3TrackPtr track, I3Position& pos)
{
  if (track->IsStopping() || track->IsContained()) {
    return pos.CalcDistance(track->GetStopPos());
  }
  return NAN;
}

//--------------------------------------------------------------
// Calculate a position on track, which is a distance 'dist' 
// away from track.Pos().
I3Position I3CalculatorImpl::ShiftAlongTrack(I3TrackPtr track, Double_t dist)
{
  I3Position p;
  Double_t x,y,z;
  x = track->GetPos().GetX() 
    + dist*sin(track->GetZenith())*cos(track->GetAzimuth());
  y = track->GetPos().GetY() 
    + dist*sin(track->GetZenith())*sin(track->GetAzimuth());
  z = track->GetPos().GetZ() 
    + dist*cos(track->GetZenith());
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
			       Double_t IndexRef)   // input
{
  //--Only calculate if track has direction
  if (track->HasDirection()) {
    I3Position P(pos);   // position (P) of a DOM or whatnot
    Double_t changle=acos(1/IndexRef); // calculate Cherenkov angle
    Double_t speed=I3Constants::c/IndexRef;

    //--Calculate position and distance of closest approach
    Double_t PT = P.CalcDistance(track->GetPos()); // T=track->Pos()
    P.ShiftCoordSystem(track->GetPos());
    P.RotateZ(-(track->GetAzimuth()));
    P.RotateY(pi/2-(track->GetZenith()));
    Double_t TA = P.GetX();
    Double_t PA = sqrt(PT*PT-TA*TA);

    //--Return position and distance of closest approach
    appos = ShiftAlongTrack(track,TA); // position A
    apdist = PA; // distance of closest approach

    //--Calculate Cherenkov photon... position on track and time of PMT hit
    Double_t CA = PA/tan(changle);
    Double_t CP = PA/sin(changle);
    Double_t TC = TA-CA;
    chpos = ShiftAlongTrack(track,TC); // Cherenkov position C
    chtime = TC/I3Constants::c + CP/speed;
          // total photon time from T (on track) through C to P.
          // TC - particle is going at c, but CP - photon is going at c/n.

    //--Is point of closest approach (A) on track?
    //--Is Cherenkov origin point (C) on track?
    if (track->IsStarting()) 
      if (track->IsStopping()) {
      //-contained track...............................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = track->GetStartPos();
	  apdist = P.CalcDistance(track->GetStartPos());
	} else if (TA>track->GetLength()) {
	  // if A is beyond STOPPING position
	  appos = track->GetStopPos();
	  apdist = P.CalcDistance(track->GetStopPos());
	}
	if (TC<0) {
	  // if C is before STARTING position
	  chpos.NullPosition();
	  chtime = NAN;
	} else if (TC>track->GetLength()) {
	  // if C is beyond STOPPING position
	  chpos.NullPosition();                                               
          chtime = NAN;
	}
      } else {
      //-starting track................................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = track->GetStartPos();
	  apdist = P.CalcDistance(track->GetStartPos());
	}
	if (TC<0) {
	  // if C is before STARTING position
	  chpos.NullPosition();
	  chtime = NAN;
	}
      }
    else
      if (track->IsStopping()) {
      //-stopping track................................
	if (TA>0) {
	  // if A is beyond STOPPING position
	  appos = track->GetStopPos();
	  apdist = P.CalcDistance(track->GetStopPos());
	}
	if (TC>0) {
	  // if C is beyond STOPPING position
	  chpos.NullPosition();
	  chtime = NAN;
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
  Double_t apdist,chtime;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime);
  if (apdist<=Precision) return kTRUE;
  else return kFALSE;
}

//--------------------------------------------------------------
// Return the distance of closets approach from I3Track to I3Position
  Double_t I3CalculatorImpl::ClosestApproachDistance(I3TrackPtr track,
						     I3Position& pos)
{
  I3Position appos,chpos;
  Double_t apdist,chtime;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime);
  return apdist;
}

//--------------------------------------------------------------
// Return the time for Cherenkov photon from I3Track to I3Position
  Double_t I3CalculatorImpl::CherenkovTime(I3TrackPtr track,
					   I3Position& pos,
					   Double_t IndexRef)
{
  I3Position appos,chpos;
  Double_t apdist,chtime;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,IndexRef);
  return chtime;
}

//--------------------------------------------------------------
// Return the time for photon from I3Cascade to I3Position
  Double_t I3CalculatorImpl::CascadeTime(I3CascadePtr cascade,
					 I3Position& pos,
					 Double_t IndexRef)
{
  Double_t castime;
  Double_t speed=I3Constants::c/IndexRef;
  castime=Distance(cascade,pos)/speed;
  return castime;
}

//--------------------------------------------------------------
