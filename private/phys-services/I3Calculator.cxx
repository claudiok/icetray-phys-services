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
I3Position I3Calculator::ShiftAlongTrack(const I3Track& track, const double dist)
{
  I3Position p;
  double x,y,z;
  x = track.GetPos().GetX() 
    - dist*sin(track.GetDir().GetZenith())*cos(track.GetDir().GetAzimuth());
  y = track.GetPos().GetY() 
    - dist*sin(track.GetDir().GetZenith())*sin(track.GetDir().GetAzimuth());
  z = track.GetPos().GetZ() 
    - dist*cos(track.GetDir().GetZenith());
  p.SetPosition(x,y,z,I3Position::car);
  return p;
}


//--------------------------------------------------------------
void I3Calculator::CherenkovCalc(const I3Track& track,        // input
				 const I3Position& position,  // input
				 I3Position& appos,     // output 
				 double& apdist,        // output
				 I3Position& chpos,     // output
				 double& chtime,        // output
				 double& chdist,        // output
				 double& chapangle,       // output
				 const double IndexRef,       // input
				 const I3OMGeo::EOrientation orient) // input
{
  //--Only calculate if track has direction
  if (track.HasDirection()) {
    I3Position P(position);   // position (P) of a DOM or whatnot
    double theta = pi - track.GetZenith();
    double phi = track.GetAzimuth() - pi;
    double changle = acos(1/IndexRef); // calculate Cherenkov angle
    double speed = c/IndexRef;

    //--Calculate position and distance of closest approach
    double PT = P.CalcDistance(track.GetPos()); // T=track.Pos()
    P.ShiftCoordSystem(track.GetPos());
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
    chtime = TC/c + CP/speed; //travel time:track Pos.I3Position
          // total photon time from T (on track) through C to P.
          // TC - particle's speed is c, but CP - photon's speed is c/n.
    chdist = CP; // distance between origin of Cherenkov light to I3Position

    //--Calculate the Cherenkov angle
    I3Position P2(position);             // position (P) of a DOM or whatnot
    P2.ShiftCoordSystem(chpos);     // get coordinates where C is origin.
    double angle = P2.GetTheta(); // return theta of new P
    if (orient==I3OMGeo::Up) { angle = pi-angle; } // in case OM points UP
    chapangle = angle;

    //--Is point of closest approach (A) on track?
    //--Is Cherenkov origin point (C) on track?
    if (track.IsStarting()) 
      if (track.IsStopping()) {
      //-contained track...............................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = (dynamic_cast<const I3Contained&>(track)).GetStartPos();
	  apdist = position.CalcDistance(appos);
	} else if (TA>track.GetLength()) {
	  // if A is beyond STOPPING position
	  appos = (dynamic_cast<const I3Contained&>(track)).GetStopPos();
	  apdist = position.CalcDistance(appos);
	}
	if (TC<0) {
	  // if C is before STARTING position
	  chpos.NullPosition();
	  chtime = NAN;
	  chdist = NAN;
	  chapangle = NAN;
	} else if (TC>track.GetLength()) {
	  // if C is beyond STOPPING position
	  chpos.NullPosition();                                               
          chtime = NAN;
	  chdist = NAN;
	  chapangle = NAN;
	}
      } else {
      //-starting track................................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = (dynamic_cast<const I3Starting&>(track)).GetStartPos();
	  apdist = position.CalcDistance(appos);
	}
	if (TC<0) {
	  // if C is before STARTING position
	  chpos.NullPosition();
	  chtime = NAN;
	  chdist = NAN;
	  chapangle = NAN;
	}
      }
    else
      if (track.IsStopping()) {
      //-stopping track................................
	if (TA>0) {
	  // if A is beyond STOPPING position
	  appos = (dynamic_cast<const I3Stopping&>(track)).GetStopPos();
	  apdist = position.CalcDistance(appos);
	}
	if (TC>0) {
	  // if C is beyond STOPPING position
	  chpos.NullPosition();
	  chtime = NAN;
	  chdist = NAN;
	  chapangle = NAN;
	}
      } else {
      //-infitine track................................
      }

  } else {
    //--Don't calculate if track does not have direction
    log_info("CherenkovCalc() - Track has no direction. Not calculating.");
    appos.NullPosition();
    apdist=NAN;
    chpos.NullPosition();
    chtime=NAN;
    chdist=NAN;
    chapangle = NAN;
  }

  return;
}


//--------------------------------------------------------------
bool I3Calculator::IsOnTrack(const I3Track& track, const I3Position& position, const double Precision)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  if (apdist<=Precision) return true;
  else return false;
}


//--------------------------------------------------------------
I3Position I3Calculator::ClosestApproachPosition(const I3Track& track, const I3Position& position)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  return appos;
}


//--------------------------------------------------------------
double I3Calculator::ClosestApproachDistance(const I3Track& track, const I3Position& position)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  return apdist;
}


//--------------------------------------------------------------
I3Position I3Calculator::CherenkovPosition(const I3Track& track, const I3Position& position)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  return chpos;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovTime(const I3Track& track, const I3Position& position, const double IndexRef)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle,
		IndexRef);
  return chtime;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovDistance(const I3Track& track, const I3Position& position)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  return chdist;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovApproachAngle(const I3Track& track, const I3Position& position, const I3OMGeo::EOrientation orient)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle,
		I3Constants::n_ice,orient);
  return chapangle;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovTime(const I3Cascade& cascade, const I3Position& position, const double IndexRef)
{
  double speed = c/IndexRef;
  return position.CalcDistance(cascade.GetPos()) / speed;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovDistance(const I3Cascade& cascade, const I3Position& position)
{
  return position.CalcDistance(cascade.GetPos());
}


//--------------------------------------------------------------
double I3Calculator::TimeResidual(const I3Track& track, const I3Position& hitpos, double hittime, const double IndexRef)
{
  double T_exp = CherenkovTime(track, hitpos, IndexRef);
  double T_meas = hittime - track.GetT();
  return T_meas - T_exp;
}


//--------------------------------------------------------------
double I3Calculator::TimeResidual(const I3Cascade& cascade, const I3Position& hitpos, double hittime, const double IndexRef)
{
  double T_exp = CherenkovTime(cascade, hitpos, IndexRef);
  double T_meas = hittime - cascade.GetT();
  return T_meas - T_exp;
}


//--------------------------------------------------------------
double I3Calculator::Angle(const I3Track& track1, const I3Track& track2)
{
  I3Direction dir1(track1.GetDir());
  I3Direction dir2(track2.GetDir());
  dir1.RotateZ(-dir2.CalcPhi());
  dir1.RotateY(-dir2.CalcTheta());
  double theta = dir1.CalcTheta();
  return theta;
}


//--------------------------------------------------------------
double I3Calculator::Distance(const I3Cascade& casc1, const I3Cascade& casc2)
{
  return casc1.GetPos().CalcDistance(casc2.GetPos());
}


//--------------------------------------------------------------
I3Position I3Calculator::InTrackSystem(const I3Direction& direction, const I3Position& pos)
{
  I3Position p(pos);
  p.RotateZ(-direction.CalcPhi());
  p.RotateY(-direction.CalcTheta());
  //p.RotateZ(direction.CalcPhi()); //get x-y orientation right
  p.RotateZ(pi/2.); //###
  return p;
}


//--------------------------------------------------------------
I3Direction I3Calculator::InTrackSystem(const I3Direction& direction, const I3Direction& dir)
{
  I3Direction d(dir);
  d.RotateZ(-direction.CalcPhi());
  d.RotateY(-direction.CalcTheta());
  //d.RotateZ(direction.CalcPhi()); //get x-y orientation right
  d.RotateZ(pi/2.); //###
  return d;
}


//--------------------------------------------------------------
I3Position I3Calculator::InTrackSystem(const I3Track& track, const I3Position& pos)
{
  return InTrackSystem(track.GetDir(), pos);
}


//--------------------------------------------------------------
I3Direction I3Calculator::InTrackSystem(const I3Track& track, const I3Direction& dir)
{
  return InTrackSystem(track.GetDir(), dir);
}


//--------------------------------------------------------------
I3Position I3Calculator::InNominalSystem(const I3Direction& direction, const I3Position& pos)
{
  I3Position p(pos);
  //p.RotateZ(-direction.CalcPhi()); //get x-y orientation right
  p.RotateZ(-pi/2.); //###
  p.RotateY(direction.CalcTheta());
  p.RotateZ(direction.CalcPhi());
  return p;
}


//--------------------------------------------------------------
I3Direction I3Calculator::InNominalSystem(const I3Direction& direction, const I3Direction& dir)
{
  I3Direction d(dir);
  //d.RotateZ(-direction.CalcPhi()); //get x-y orientation right
  d.RotateZ(-pi/2.); //###
  d.RotateY(direction.CalcTheta());
  d.RotateZ(direction.CalcPhi());
  return d;
}


//--------------------------------------------------------------
I3Position I3Calculator::InNominalSystem(const I3Track& track, const I3Position& pos)
{
  return InNominalSystem(track.GetDir(), pos);
}


//--------------------------------------------------------------
I3Direction I3Calculator::InNominalSystem(const I3Track& track, const I3Direction& dir)
{
  return InNominalSystem(track.GetDir(), dir);
}

