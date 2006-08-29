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
#if KATH_MESSING_AROUND
void I3Calculator::CherenkovCalc(const I3Particle& particle,  // input
				 const I3Position& position,  // input
				 I3Position& chpos,           // output
				 double& chtime,              // output
				 double& chdist,              // output
				 double& chapangle,           // output
				 const double IndexRefG,      // input
				 const double IndexRefP,      // input
				 const I3OMGeo::Orientation orient) // input
{
  I3Position appos;     // output 
  double apdist;        // output
  //--Only calculate if particle has a direction
  if(particle.HasDirection()) 
  {
    double changle = acos(1/IndexRefP); // calculate Cherenkov angle

    I3Position appos_ss;
    double apdist_ss;
    ClosestApproachCalc(particle,position, appos, apdist, appos_ss, apdist_ss);
    double s = DistanceAlongTrack(particle, appos); //distance between track position and closest approach position

    chdist = apdist/sin(changle);  //distance between cherenkov position and OM
    double a = s - apdist/tan(changle); //distance between track position and cherenkov position
    chtime = (a + chdist*IndexRefG)/c; //time between track position and OM

    double pos1_x = particle.GetX() + a*particle.GetDir().GetX(); //cher pos
    double pos1_y = particle.GetY() + a*particle.GetDir().GetY();
    double pos1_z = particle.GetZ() + a*particle.GetDir().GetZ();
    chpos.SetPosition(pos1_x, pos1_y, pos1_z);

    double chdist_z = position.GetZ() - particle.GetZ() - a*particle.GetDir().GetZ();  //z component of vector between cherenkov position and OM

    //angle between (vector between cherenkov position and OM) 
    //and (OM axis - can be seen as a vector with (0, 0, +/-1))
    if(orient==I3OMGeo::Up) {chapangle = pi-acos(chdist_z/chdist);}  
    if(orient==I3OMGeo::Down) {chapangle = pi-acos(-chdist_z/chdist);}

    if((particle.GetShape()==I3Particle::StartingTrack && a<0) || 
             //track starts after pos1 (cherenkov point)
       (particle.GetShape()==I3Particle::StoppingTrack && a>0) || 
             //track stops before pos1 (cherenkov point)
       (particle.GetShape()==I3Particle::ContainedTrack && 
         (a<0 || particle.GetLength()<a)))  
             //track starts after or stops before pos1 (cherenkov point)
    { 
      chpos.NullPosition();
      chtime = NAN;
      chdist = NAN;
      chapangle = NAN;
    }

  }
  else
  {
    //--Don't calculate if track does not have direction
    log_fatal("CherenkovCalc() - particle has no direction. Not calculating.");
  }
  return;
}
#else
// Here is the old version, which computed both ClosestApproach and Cherenkov stuff:
void I3Calculator::CherenkovCalc(const I3Particle& particle,  // input
				 const I3Position& position,  // input
				 I3Position& appos,           // output 
				 double& apdist,              // output
				 I3Position& chpos,           // output
				 double& chtime,              // output
				 double& chdist,              // output
				 double& chapangle,           // output
				 const double IndexRefG,      // input
				 const double IndexRefP,      // input
				 const I3OMGeo::Orientation orient) // input
{
  //--Only calculate if particle is track
  if(particle.HasDirection()) 
  {
    double changle = acos(1/IndexRefP); // calculate Cherenkov angle

    double theta  = particle.GetZenith();
    double phi    = particle.GetAzimuth();
    double pos0_x = particle.GetX();
    double pos0_y = particle.GetY();
    double pos0_z = particle.GetZ();

    double e_x = -sin(theta)*cos(phi);  //unit vector of direction of particle
    double e_y = -sin(theta)*sin(phi);
    double e_z = -cos(theta);

    double h_x = position.GetX() - pos0_x;  //vector between particle position and OM
    double h_y = position.GetY() - pos0_y;
    double h_z = position.GetZ() - pos0_z;

    double s = e_x*h_x + e_y*h_y + e_z*h_z; //distance between particle position and closest approach position

    double pos2_x = pos0_x + s*e_x; //closest approach position
    double pos2_y = pos0_y + s*e_y;
    double pos2_z = pos0_z + s*e_z;

    appos.SetPosition(pos2_x, pos2_y, pos2_z); //closest approach position
    apdist = position.CalcDistance(appos);  //closest approach distance

    chdist = apdist/sin(changle);  //distance between cherenkov position and OM
    double a = s - apdist/tan(changle); //distance between particle position and cherenkov position
    chtime = (a + chdist*IndexRefG)/c; //time between particle position and OM

    double pos1_x = pos0_x + a*e_x;  //cherenkov position
    double pos1_y = pos0_y + a*e_y;
    double pos1_z = pos0_z + a*e_z;
    chpos.SetPosition(pos1_x, pos1_y, pos1_z);

    double chdist_z = h_z - a*e_z;  //z component of vector between cherenkov position and OM

    //angle between (vector between cherenkov position and OM) 
    //and (OM axis - can be seen as a vector with (0, 0, +/-1))
    if(orient==I3OMGeo::Up) {chapangle = pi-acos(chdist_z/chdist);}  
    if(orient==I3OMGeo::Down) {chapangle = pi-acos(-chdist_z/chdist);}

    if((particle.GetShape()==I3Particle::StartingTrack && a<0) || 
             //track starts after pos1 (cherenkov point)
       (particle.GetShape()==I3Particle::StoppingTrack && a>0) || 
             //track stops before pos1 (cherenkov point)
       (particle.GetShape()==I3Particle::ContainedTrack && 
         (a<0 || particle.GetLength()<a)))  
             //track starts after or stops before pos1 (cherenkov point)
    { 
      chpos.NullPosition();
      chtime = NAN;
      chdist = NAN;
      chapangle = NAN;
    }

    if((particle.GetShape()==I3Particle::StartingTrack && s<0) || 
                  //track starts after pos2 (closest approach position)
       (particle.GetShape()==I3Particle::StoppingTrack && s>0) || 
                  //track stops before pos2 (closest approach position)
       (particle.GetShape()==I3Particle::ContainedTrack && s<0))
                  //track starts after pos2 (closest approach position)
    { 
      appos = particle.GetPos();
      apdist = position.CalcDistance(appos);
    }
    if(particle.GetShape()==I3Particle::ContainedTrack && particle.GetLength()<s)
                  //track stops before pos2 (closest approach position)
    {
      appos = particle.GetStopPos();
      apdist = position.CalcDistance(appos);
    }
  }
  else
  {
    //--Don't calculate if particle does not have direction
    log_fatal("CherenkovCalc() - particle has no direction. Not calculating.");
  }
  return;
}
#endif

//--------------------------------------------------------------
bool I3Calculator::IsOnTrack(const I3Particle& track, const I3Position& position, const double Precision)
{
  if (track.IsTrack()) {
#if KATH_MESSING_AROUND
    I3Position appos,appos2;
    double apdist,apdist2;
    ClosestApproachCalc(track,position,appos2,apdist2,appos,apdist);
#else
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle);
#endif
    if (apdist<=Precision) return true;
    else return false;
  }
  else return false;
}


//--------------------------------------------------------------
void I3Calculator::ClosestApproachCalc(const I3Particle& particle,
				       const I3Position& position,
				       I3Position& appos_inf,
				       double& apdist_inf,
				       I3Position& appos_stopstart,
				       double& apdist_stopstart) 
{
  if(particle.HasDirection()) 
  {
    double theta  = particle.GetZenith();
    double phi    = particle.GetAzimuth();
    double pos0_x = particle.GetX();
    double pos0_y = particle.GetY();
    double pos0_z = particle.GetZ();
    
    double e_x = -sin(theta)*cos(phi);  //unit vector of direction of particle
    double e_y = -sin(theta)*sin(phi);
    double e_z = -cos(theta);
    
    double h_x = position.GetX() - pos0_x;  //vector between particle position and OM
    double h_y = position.GetY() - pos0_y;
    double h_z = position.GetZ() - pos0_z;
    
    double s = e_x*h_x + e_y*h_y + e_z*h_z; //distance between particle position and closest approach position
    
    double pos2_x = pos0_x + s*e_x; //closest approach position
    double pos2_y = pos0_y + s*e_y;
    double pos2_z = pos0_z + s*e_z;
    
    appos_inf.SetPosition(pos2_x, pos2_y, pos2_z); //closest approach position
    apdist_inf = position.CalcDistance(appos_inf);  //closest approach distance
    
    // Adjustment for contained/stopping/starting tracks
    appos_stopstart.SetPosition(appos_inf);
    apdist_stopstart = apdist_inf;
    if((particle.GetShape()==I3Particle::StartingTrack && s<0) || 
       //track starts after pos2 (closest approach position)
       (particle.GetShape()==I3Particle::StoppingTrack && s>0) || 
       //track stops before pos2 (closest approach position)
       (particle.GetShape()==I3Particle::ContainedTrack && s<0))
      //track starts after pos2 (closest approach position)
      { 
	appos_stopstart = particle.GetPos();
	apdist_stopstart = position.CalcDistance(appos_stopstart);
      }
    if(particle.GetShape()==I3Particle::ContainedTrack && particle.GetLength()<s)
      //track stops before pos2 (closest approach position)
      {
	appos_stopstart = particle.GetStopPos();
	apdist_stopstart = position.CalcDistance(appos_stopstart);
      }
  } // if it has direction
  else
  {
    //--Don't calculate if particle does not have direction
    log_fatal("ClosestApproachCalc() - particle has no direction. Not calculating.");
  }
  return;
}

//--------------------------------------------------------------
I3Position I3Calculator::ClosestApproachPosition(const I3Particle& particle, const I3Position& position)
{
  if (particle.IsTrack()) {
#if KATH_MESSING_AROUND
    I3Position appos,appos2;
    double apdist,apdist2;
    ClosestApproachCalc(particle,position,appos2,apdist2,appos,apdist);
#else
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
   CherenkovCalc(particle,position,appos,apdist,chpos,chtime,chdist,chapangle);
#endif
    return appos;
  }
  else if (particle.IsCascade()) {
    return particle.GetPos();
  }
  else {
    I3Position nullpos;
    return nullpos;
  }
}


//--------------------------------------------------------------
double I3Calculator::ClosestApproachDistance(const I3Particle& particle, const I3Position& position)
{
  if (particle.IsTrack()) {
#if KATH_MESSING_AROUND
    I3Position appos,appos2;
    double apdist,apdist2;
    ClosestApproachCalc(particle,position,appos2,apdist2,appos,apdist);
#else
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
   CherenkovCalc(particle,position,appos,apdist,chpos,chtime,chdist,chapangle);
#endif
    return apdist;
  }
  else if (particle.IsCascade()) {
    return position.CalcDistance(particle.GetPos());
  }
  else return NAN;
}


//--------------------------------------------------------------
double I3Calculator::DistanceAlongTrack(const I3Particle& track, const I3Position& ompos) {
  if (track.IsTrack()) {
    I3Position pos(ompos);
    pos.ShiftCoordSystem(track.GetPos());
    pos.RotateZ(-track.GetDir().CalcPhi());
    pos.RotateY(-track.GetDir().CalcTheta());
    return pos.GetZ();
  }
  else return NAN;
}

//--------------------------------------------------------------
I3Position I3Calculator::CherenkovPosition(const I3Particle& particle, const I3Position& position)
{
  if (particle.IsTrack()) {
#if KATH_MESSING_AROUND
    I3Position chpos;
    double chtime,chdist,chapangle;
    CherenkovCalc(particle,position,chpos,chtime,chdist,chapangle);
#else
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
   CherenkovCalc(particle,position,appos,apdist,chpos,chtime,chdist,chapangle);
#endif
    return chpos;
  }
  else if (particle.IsCascade()) {
    return particle.GetPos();
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
#if KATH_MESSING_AROUND
    I3Position chpos;
    double chtime,chdist,chapangle;
    CherenkovCalc(particle, position, chpos, chtime, chdist,
		  chapangle, IndexRefG, IndexRefP);
#else
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(particle, position, appos, apdist, chpos, chtime, chdist,
		  chapangle, IndexRefG, IndexRefP);
#endif
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
#if KATH_MESSING_AROUND
    I3Position chpos;
    double chtime,chdist,chapangle;
    CherenkovCalc(particle, position, chpos, chtime, chdist,
		  chapangle);
#else
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(particle, position, appos, apdist, chpos, chtime, chdist,
		  chapangle);
#endif
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
#if KATH_MESSING_AROUND
    I3Position chpos;
    double chtime,chdist,chapangle;
    CherenkovCalc(track,position,chpos,chtime,chdist,chapangle,
		  I3Constants::n_ice_group,n_ice_phase,orient);
#else
    I3Position appos,chpos;
    double apdist,chtime,chdist,chapangle;
    CherenkovCalc(track,position,appos,apdist,chpos,chtime,chdist,chapangle,
		  I3Constants::n_ice_group,n_ice_phase,orient);
#endif
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
double I3Calculator::Angle(const I3Particle& p1, const I3Particle& p2)
{
  I3Direction dir1(p1.GetDir());
  I3Direction dir2(p2.GetDir());
  dir1.RotateZ(-dir2.CalcPhi());
  dir1.RotateY(-dir2.CalcTheta());
  double theta = dir1.CalcTheta();
  return theta;
}

//--------------------------------------------------------------
double I3Calculator::Distance(const I3Particle& p1, const I3Particle& p2)
{
  return p1.GetPos().CalcDistance(p2.GetPos());
}

//--------------------------------------------------------------
double I3Calculator::FourDistance(const I3Particle& p1, const I3Particle& p2)
{
  // 4-distance here is defined as:
  //   sqrt( (ct1-ct2)^2 - (x1-x2)^2 + (y1-y2)^2 + (z1-z2)^2 )
  return sqrt(abs(pow(I3Constants::c*(p1.GetTime()-p2.GetTime()),2) - 
		  pow(p1.GetX()-p2.GetX(),2) -
		  pow(p1.GetY()-p2.GetY(),2) -
		  pow(p1.GetZ()-p2.GetZ(),2)));
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

