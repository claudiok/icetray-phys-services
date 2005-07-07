/**
    copyright  (C) 2004
    the icecube collaboration
    $Id$

    @version $Revision: 1.1 $
    @date $Date$
    @author

    @todo

*/
#include "phys-services/I3Calculator.h"
#include "dataclasses/I3Starting.h"
#include "dataclasses/I3Stopping.h"
#include "dataclasses/I3Contained.h"
#include "dataclasses/I3OMResponse.h"
#include "dataclasses/I3AMANDAAnalogReadout.h"

using namespace std;


//--------------------------------------------------------------
void I3Calculator::CherenkovCalc(I3TrackPtr track,   // input
				 I3Position& pos,    // input
				 I3Position& appos,  // output 
				 double& apdist,     // output
				 I3Position& chpos,  // output
				 double& chtime,     // output
				 double& chdist,     // output
				 double IndexRef)    // input
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
	  appos = (boost::dynamic_pointer_cast<I3Contained>(track))
	    ->GetStartPos();
	  apdist = pos.CalcDistance(appos);
	} else if (TA>track->GetLength()) {
	  // if A is beyond STOPPING position
	  appos = (boost::dynamic_pointer_cast<I3Contained>(track))
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
	  appos = (boost::dynamic_pointer_cast<I3Starting>(track))
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
	  appos = (boost::dynamic_pointer_cast<I3Stopping>(track))
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
    log_info("CherenkovLight - Track has no direction. Not calculating.");
    appos.NullPosition();
    apdist=NAN;
    chpos.NullPosition();
    chtime=NAN;
  }
}


//--------------------------------------------------------------
I3Position I3Calculator::ShiftAlongTrack(I3TrackPtr track, double dist)
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
bool I3Calculator::IsOnTrack(I3TrackPtr track, I3Position& pos, double Precision)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  if (apdist<=Precision) return kTRUE;
  else return kFALSE;
}


//--------------------------------------------------------------
double I3Calculator::ClosestApproachDistance(I3TrackPtr track, I3Position& pos)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  return apdist;
}


//--------------------------------------------------------------
I3Position I3Calculator::ClosestApproachPosition(I3TrackPtr track, I3Position& pos)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  return appos;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovDistance(I3TrackPtr track, I3Position& pos)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist);
  return chdist;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovTime(I3TrackPtr track, I3Position& pos, 
				   double IndexRef)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist;
  CherenkovCalc(track,pos,appos,apdist,chpos,chtime,chdist,IndexRef);
  return chtime;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovAngle(I3TrackPtr track, I3Position& pos,
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
double I3Calculator::CascadeDistance(I3CascadePtr cascade, I3Position& pos)
{
  return pos.CalcDistance(cascade->GetPos());
}


//--------------------------------------------------------------
double I3Calculator::CascadeDistance(I3CascadePtr casc1, I3CascadePtr casc2)
{
  return casc1->GetPos().CalcDistance(casc2->GetPos());
}


//--------------------------------------------------------------
double I3Calculator::CascadeTime(I3CascadePtr cascade, I3Position& pos, 
				 double IndexRef)
{
  double speed = c/IndexRef;
  return pos.CalcDistance(cascade->GetPos())/speed;
}


//--------------------------------------------------------------
double I3Calculator::AngleDiff(I3TrackPtr track1, I3TrackPtr track2)
{
  I3Direction dir1(track1->GetDir());
  I3Direction dir2(track2->GetDir());
  dir1.RotateZ(-dir2.CalcPhi());
  dir1.RotateY(-dir2.CalcTheta());
  double theta = dir1.CalcTheta();
  return theta;
}
