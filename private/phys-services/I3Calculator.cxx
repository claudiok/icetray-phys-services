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
				 const double IndexRefG,       // input
				 const double IndexRefP,       // input
				 const I3OMGeo::Orientation orient) // input
{
  //--Only calculate if particle is track
  if(track.IsTrack()) 
  {
    double changle = acos(1/IndexRefP); // calculate Cherenkov angle

    double theta  = track.GetZenith();
    double phi    = track.GetAzimuth();
    double pos0_x = track.GetX();
    double pos0_y = track.GetY();
    double pos0_z = track.GetZ();

    double e_x = -sin(theta)*cos(phi);  //unit vector of direction of track
    double e_y = -sin(theta)*sin(phi);
    double e_z = -cos(theta);

    double h_x = position.GetX() - pos0_x;  //vector between track position and OM
    double h_y = position.GetY() - pos0_y;
    double h_z = position.GetZ() - pos0_z;

    double s = e_x*h_x + e_y*h_y + e_z*h_z; //distance between track position and closest approach position

    double pos2_x = pos0_x + s*e_x; //closest approach position
    double pos2_y = pos0_y + s*e_y;
    double pos2_z = pos0_z + s*e_z;

    appos.SetPosition(pos2_x, pos2_y, pos2_z); //closest approach position
    apdist = position.CalcDistance(appos);  //closest approach distance

    chdist = apdist/sin(changle);  //distance between cherenkov position and OM
    double a = s - apdist/tan(changle); //distance between track position and cherenkov position
    chtime = (a + chdist*IndexRefG)/c; //time between track position and OM

    double pos1_x = pos0_x + a*e_x;  //cherenkov position
    double pos1_y = pos0_y + a*e_y;
    double pos1_z = pos0_z + a*e_z;
    chpos.SetPosition(pos1_x, pos1_y, pos1_z);

    double chdist_z = h_z - a*e_z;  //z component of vector between cherenkov position and OM
    //angle between (vector between cherenkov position and OM) 
    //and (OM axis - can be seen as a vector with (0, 0, +/-1))
    if(orient==I3OMGeo::Up) {chapangle = pi-acos(chdist_z/chdist);}  
    if(orient==I3OMGeo::Down) {chapangle = pi-acos(-chdist_z/chdist);}

    if((track.GetShape()==I3Particle::StartingTrack && a<0) || 
             //track starts after pos1 (cherenkov point)
       (track.GetShape()==I3Particle::StoppingTrack && a>0) || 
             //track stops before pos1 (cherenkov point)
       (track.GetShape()==I3Particle::ContainedTrack && 
         (a<0 || track.GetLength()<a)))  
             //track starts after or stops before pos1 (cherenkov point)
    { 
      chpos.NullPosition();
      chtime = NAN;
      chdist = NAN;
      chapangle = NAN;
    }

    if((track.GetShape()==I3Particle::StartingTrack && s<0) || 
                  //track starts after pos2 (closest approach position)
       (track.GetShape()==I3Particle::StoppingTrack && s>0) || 
                  //track stops before pos2 (closest approach position)
       (track.GetShape()==I3Particle::ContainedTrack && s<0))
                  //track starts after pos2 (closest approach position)
    { 
      appos = track.GetPos();
      apdist = position.CalcDistance(appos);
    }
    if(track.GetShape()==I3Particle::ContainedTrack && track.GetLength()<s)
                  //track stops before pos2 (closest approach position)
    {
      appos = track.GetStopPos();
      apdist = position.CalcDistance(appos);
    }
  }
  else
  {
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
double I3Calculator::CherenkovTime(const I3Particle& particle, const I3Position& position, const double IndexRefG, const double IndexRefP )
{
  if (particle.IsTrack()) {
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(particle, position, appos, apdist, chpos, chtime, chdist,
		  chapangle, IndexRefG, IndexRefP);
    return chtime;
  }
  else if (particle.IsCascade()) {
    double speed = c/IndexRefG;
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
		  I3Constants::n_ice_group,n_ice_phase,orient);
    return chapangle;
  }
  else return NAN;
}

//--------------------------------------------------------------
double I3Calculator::TimeResidual(const I3Particle& particle, const I3Position& hitpos, double hittime, const double IndexRefG, const double IndexRefP)
{
  double T_exp = CherenkovTime(particle, hitpos, IndexRefG, IndexRefP );
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

