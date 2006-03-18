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
  //--Only calculate if particle is track
  if (track.IsTrack()) {

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
    appos = track.ShiftAlongTrack(TA); // position A
    apdist = PA; // distance of closest approach
  
    //--Calculate Cherenkov photon... position on track and time of PMT hit
    double CA = PA/tan(changle);
    double CP = PA/sin(changle);
    double TC = TA-CA;
    chpos = track.ShiftAlongTrack(TC); // origin of Cherenkov light (C)
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

    // The effective distance (d_eff) due to scattering in the ice.
    // We don't really expect direct hits ever.
    // Maybe we should use this d_eff instead of d (CP) in calculating 
    // expected time of arrival of photons.
    //double d_eff=3.1-3.9*cos_eta+4.6*cos_eta*cos_eta+0.84 * sin(changle)*CP;

    //--Is point of closest approach (A) on track?
    //--Is Cherenkov origin point (C) on track?
    if (track.GetShape()==I3Particle::StartingTrack) 
      if (track.GetShape()==I3Particle::StoppingTrack) {
	//-contained track...............................
	if (TA<0) {
	  // if A is before STARTING position
	  appos = track.GetStartPos();
	  apdist = position.CalcDistance(appos);
	} else if (TA>track.GetLength()) {
	  // if A is beyond STOPPING position
	  appos = track.GetStopPos();
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
	  appos = track.GetStartPos();
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
      if (track.GetShape()==I3Particle::StoppingTrack) {
	//-stopping track................................
	if (TA>0) {
	  // if A is beyond STOPPING position
	  appos = track.GetStopPos();
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
    log_fatal("CherenkovCalc() - I3Particle is no a track. Not calculating.");
  }

  return;
}


//--------------------------------------------------------------
bool I3Calculator::IsOnTrack(const I3Particle& track, const I3Position& position, const double Precision)
{
  if (track.IsTrack()) {
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
    if (apdist<=Precision) return true;
    else return false;
  }
  else return false;
}


//--------------------------------------------------------------
I3Position I3Calculator::ClosestApproachPosition(const I3Particle& track, const I3Position& position)
{
  if (track.IsTrack()) {
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
    return appos;
  }
  else {
    I3Position nullpos;
    return nullpos;
  }
}


//--------------------------------------------------------------
double I3Calculator::ClosestApproachDistance(const I3Particle& track, const I3Position& position)
{
  if (track.IsTrack()) {
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
    return apdist;
  }
  else return NAN;
}


//--------------------------------------------------------------
I3Position I3Calculator::CherenkovPosition(const I3Particle& track, const I3Position& position)
{
  if (track.IsTrack()) {
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
    return chpos;
  }
  else {
    I3Position nullpos;
    return nullpos;
  }
}


//--------------------------------------------------------------
double I3Calculator::CherenkovTime(const I3Particle& particle, const I3Position& position, const double IndexRef)
{
  if (particle.IsTrack()) {
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(particle, position, appos, apdist, chpos, chtime, chdist,
		  chapangle, IndexRef);
    return chtime;
  }
  else if (particle.IsCascade()) {
    double speed = c/IndexRef;
    return position.CalcDistance(particle.GetPos()) / speed;
  }
  else return NAN;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovDistance(const I3Particle& particle, const I3Position& position)
{
  if (particle.IsTrack()) {
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(particle, position, appos, apdist, chpos, chtime, chdist,
		  chapangle);
    return chdist;
  }
  else if (particle.IsCascade()) {
    return position.CalcDistance(particle.GetPos());
  }
  else return NAN;
}


//--------------------------------------------------------------
double I3Calculator::CherenkovApproachAngle(const I3Particle& track, const I3Position& position, const I3OMGeo::Orientation orient)
{
  if (track.IsTrack()) {
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle,
		  I3Constants::n_ice,orient);
    return chapangle;
  }
  else return NAN;
}

//--------------------------------------------------------------
double I3Calculator::TimeResidual(const I3Particle& particle, const I3Position& hitpos, double hittime, const double IndexRef)
{
  double T_exp = CherenkovTime(particle, hitpos, IndexRef);
  double T_meas = hittime - particle.GetTime();
  return T_meas - T_exp;
}

//--------------------------------------------------------------
double I3Calculator::Angle(const I3Particle& track1, const I3Particle& track2)
{
  if (track1.IsTrack() && track1.IsTrack()) {
    I3Direction dir1(track1.GetDir());
    I3Direction dir2(track2.GetDir());
    dir1.RotateZ(-dir2.CalcPhi());
    dir1.RotateY(-dir2.CalcTheta());
    double theta = dir1.CalcTheta();
    return theta;
  }
  else return NAN;
}

//--------------------------------------------------------------
double I3Calculator::Distance(const I3Particle& casc1, const I3Particle& casc2)
{
  if (casc1.IsCascade() && casc2.IsCascade()) {
    return casc1.GetPos().CalcDistance(casc2.GetPos());
  }
  else return NAN;
}

//--------------------------------------------------------------
I3Position I3Calculator::InTrackSystem(const I3Direction& direction, const I3Position& pos)
{
  I3Position p(pos);
  p.RotateZ(-direction.CalcPhi());
  p.RotateY(-direction.CalcTheta());
  p.RotateZ(direction.CalcPhi()); //get x-y orientation right
  return p;
}


//--------------------------------------------------------------
I3Direction I3Calculator::InTrackSystem(const I3Direction& direction, const I3Direction& dir)
{
  I3Direction d(dir);
  d.RotateZ(-direction.CalcPhi());
  d.RotateY(-direction.CalcTheta());
  d.RotateZ(direction.CalcPhi()); //get x-y orientation right
  return d;
}


//--------------------------------------------------------------
I3Position I3Calculator::InTrackSystem(const I3Particle& track, const I3Position& pos)
{
  if (track.IsTrack()) {
    return InTrackSystem(track.GetDir(), pos);
  }
  else {
    I3Position nullpos;
    return nullpos;
  }
}


//--------------------------------------------------------------
I3Direction I3Calculator::InTrackSystem(const I3Particle& track, const I3Direction& dir)
{
  if (track.IsTrack()) {
    return InTrackSystem(track.GetDir(), dir);
  }
  else {
    I3Direction nulldir;
    return nulldir;
  }
}


//--------------------------------------------------------------
I3Position I3Calculator::InNominalSystem(const I3Direction& direction, const I3Position& pos)
{
  I3Position p(pos);
  p.RotateZ(-direction.CalcPhi()); //get x-y orientation right
  p.RotateY(direction.CalcTheta());
  p.RotateZ(direction.CalcPhi());
  return p;
}


//--------------------------------------------------------------
I3Direction I3Calculator::InNominalSystem(const I3Direction& direction, const I3Direction& dir)
{
  I3Direction d(dir);
  d.RotateZ(-direction.CalcPhi()); //get x-y orientation right
  d.RotateY(direction.CalcTheta());
  d.RotateZ(direction.CalcPhi());
  return d;
}


//--------------------------------------------------------------
I3Position I3Calculator::InNominalSystem(const I3Particle& track, const I3Position& pos)
{
  if (track.IsTrack()) {
    return InNominalSystem(track.GetDir(), pos);
  }
  else {
    I3Position nullpos;
    return nullpos;
  }
}


//--------------------------------------------------------------
I3Direction I3Calculator::InNominalSystem(const I3Particle& track, const I3Direction& dir)
{
  if (track.IsTrack()) {
    return InNominalSystem(track.GetDir(), dir);
  }
  else {
    I3Direction nulldir;
    return nulldir;
  }
}

