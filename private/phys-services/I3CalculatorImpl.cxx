/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3CalculatorImpl.cxx,v 1.1 2004/06/24 15:04:54 dule Exp $

    @version $Revision: 1.1 $
    @date $Date: 2004/06/24 15:04:54 $
    @author

    @todo

*/
#include "phys-services/I3CalculatorImpl.h"
#include "dataclasses/I3Constants.h"
#include <iostream>

using namespace std;
using namespace I3Constants;

//--------------------------------------------------------------
// Calculate distance to position Pos() on track
Double_t I3CalculatorImpl::Distance(I3Track* track, I3Position& pos)
{
  return pos.CalcDistance(track->Pos());
}

//--------------------------------------------------------------
// Calculate distance to START position on track
Double_t I3CalculatorImpl::StartDistance(I3Track* track, I3Position& pos)
{
  if (track->IsStarting() || track->IsContained()) {
    return pos.CalcDistance(track->StartPos());
  }
  return NAN;
}

//--------------------------------------------------------------
// Calculate distance to STOP position on track
Double_t I3CalculatorImpl::StopDistance(I3Track* track, I3Position& pos)
{
  if (track->IsStopping() || track->IsContained()) {
    return pos.CalcDistance(track->StopPos());
  }
  return NAN;
}

//--------------------------------------------------------------
// Calculate a position on track, which is a distance 'dist' 
// away from track.Pos().
I3Position I3CalculatorImpl::ShiftAlongTrack(I3Track* track, Double_t dist)
{
  I3Position p;
  Double_t x,y,z;
  x = track->Pos().X() + dist*sin(track->Zenith())*cos(track->Azimuth());
  y = track->Pos().Y() + dist*sin(track->Zenith())*sin(track->Azimuth());
  z = track->Pos().Z() + dist*cos(track->Zenith());
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
			       Double_t ChAngle)   // input
{
  //--Only calculate if track has direction
  if (track->HasDirection()) {
    I3Position P(pos);   // position (P) of a DOM or whatnot

    //--Calculate position and distance of closest approach
    Double_t PT = P.CalcDistance(track->Pos()); // T=track->Pos()
    P.ShiftCoordSystem(track->Pos());
    P.RotateZ(-(track->Azimuth()));
    P.RotateY(pi/2-(track->Zenith()));
    Double_t TA = P.X();
    Double_t PA = sqrt(PT*PT-TA*TA);

    //--Return position and distance of closest approach
    appos = ShiftAlongTrack(track,TA); // position A
    apdist = PA; // distance of closest approach

    //--Calculate Cherenkov photon... position on track and time of PMT hit
    Double_t CA = PA/tan(ChAngle);
    Double_t CP = PA/sin(ChAngle);
    Double_t TC = TA-CA;
    chpos = ShiftAlongTrack(track,TC); // Cherenkov position C
    chtime = (TC+CP)/c / I3Units::ns;
               // total photon time from T (on track) through C to P.

    //--Is point of closest approach (A) on track?
    //--Is Cherenkov origin point (C) on track?
    if (track->IsStarting()) 
      if (track->IsStopping()) {
      //-contained track...............................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = track->StartPos();
	  apdist = P.CalcDistance(track->StartPos());
	} else if (TA>track->Length()) {
	  // if A is beyond STOPPING position
	  appos = track->StopPos();
	  apdist = P.CalcDistance(track->StopPos());
	}
	if (TC<0) {
	  // if C is before STARTING position
	  chpos.NullPosition();
	  chtime = NAN;
	} else if (TC>track->Length()) {
	  // if C is beyond STOPPING position
	  chpos.NullPosition();                                               
          chtime = NAN;
	}
      } else {
      //-starting track................................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = track->StartPos();
	  apdist = P.CalcDistance(track->StartPos());
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
	  appos = track->StopPos();
	  apdist = P.CalcDistance(track->StopPos());
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
Bool_t I3CalculatorImpl::IsOnTrack(I3Track* track, 
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
// Return the time for Cherenkov photon from I3Track to I3Position
  Double_t I3CalculatorImpl::CherenkovTime(I3TrackPtr track,
				     I3Position& pos,
				     Double_t ChAngle)
{
  I3Position appos,chpos;
  Double_t apdist,chtime;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,ChAngle);
  return chtime;
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
