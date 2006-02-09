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

using namespace std;


//--------------------------------------------------------------
I3Position I3Calculator::ShiftAlongTrack(const I3Particle& track, const double dist)
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
void I3Calculator::CherenkovCalc(const I3Particle& track,        // input
				 const I3Position& position,  // input
				 I3Position& appos,     // output 
				 double& apdist,        // output
				 I3Position& chpos,     // output
				 double& chtime,        // output
				 double& chdist,        // output
				 double& chapangle,       // output
				 const double IndexRef,       // input
				 const I3OMGeo::Orientation orient) // input
{
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
  
  return;
}


//--------------------------------------------------------------
bool I3Calculator::IsOnTrack(const I3Particle& track, const I3Position& position, const double Precision)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  if (apdist<=Precision) return true;
  else return false;
}


//--------------------------------------------------------------
I3Position I3Calculator::ClosestApproachPosition(const I3Particle& track, const I3Position& position)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  return appos;
}


//--------------------------------------------------------------
double I3Calculator::ClosestApproachDistance(const I3Particle& track, const I3Position& position)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  return apdist;
}


//--------------------------------------------------------------
I3Position I3Calculator::CherenkovPosition(const I3Particle& track, const I3Position& position)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  return chpos;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovTime(const I3Particle& track, const I3Position& position, const double IndexRef)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle,
		IndexRef);
  return chtime;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovDistance(const I3Particle& track, const I3Position& position)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
  return chdist;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovApproachAngle(const I3Particle& track, const I3Position& position, const I3OMGeo::Orientation orient)
{
  I3Position appos,chpos;
  double apdist,chtime,chdist,chapangle;
  CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle,
		I3Constants::n_ice,orient);
  return chapangle;
}

#warning comment out cascade stuff
#if 0
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
#endif

//--------------------------------------------------------------
double I3Calculator::TimeResidual(const I3Particle& track, const I3Position& hitpos, double hittime, const double IndexRef)
{
  double T_exp = CherenkovTime(track, hitpos, IndexRef);
  double T_meas = hittime - track.GetT();
  return T_meas - T_exp;
}

#warning comment out cascade stuff
#if 0
//--------------------------------------------------------------
double I3Calculator::TimeResidual(const I3Cascade& cascade, const I3Position& hitpos, double hittime, const double IndexRef)
{
  double T_exp = CherenkovTime(cascade, hitpos, IndexRef);
  double T_meas = hittime - cascade.GetT();
  return T_meas - T_exp;
}
#endif

//--------------------------------------------------------------
double I3Calculator::Angle(const I3Particle& track1, const I3Particle& track2)
{
  I3Direction dir1(track1.GetDir());
  I3Direction dir2(track2.GetDir());
  dir1.RotateZ(-dir2.CalcPhi());
  dir1.RotateY(-dir2.CalcTheta());
  double theta = dir1.CalcTheta();
  return theta;
}

#warning comment out cascade stuff
#if 0
//--------------------------------------------------------------
double I3Calculator::Distance(const I3Cascade& casc1, const I3Cascade& casc2)
{
  return casc1.GetPos().CalcDistance(casc2.GetPos());
}
#endif 

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
I3Position I3Calculator::InTrackSystem(const I3Particle& track, const I3Position& pos)
{
  return InTrackSystem(track.GetDir(), pos);
}


//--------------------------------------------------------------
I3Direction I3Calculator::InTrackSystem(const I3Particle& track, const I3Direction& dir)
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
I3Position I3Calculator::InNominalSystem(const I3Particle& track, const I3Position& pos)
{
  return InNominalSystem(track.GetDir(), pos);
}


//--------------------------------------------------------------
I3Direction I3Calculator::InNominalSystem(const I3Particle& track, const I3Direction& dir)
{
  return InNominalSystem(track.GetDir(), dir);
}

