/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3CalculatorTest.cxx 9161 2005-06-14 16:44:58Z pretz $

    @version $Revision: 1.2 $
    @date $Date: 2005-06-14 12:44:58 -0400 (Tue, 14 Jun 2005) $
    @author dule

    @todo
*/

#include <I3Test.h>

#include "phys-services/I3Calculator.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/I3Position.h"
#include "dataclasses/I3Direction.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
using std::string;
using std::cout;
using std::endl;
using namespace I3Units;
using namespace I3Calculator;

static I3Particle inftrack()
{
  I3Particle inftrack;
  inftrack.SetPos(0,0,0);
  inftrack.SetDir(0,1,1);
  inftrack.SetShape(I3Particle::InfiniteTrack);
  return inftrack;
}

static I3Particle muon()
{
  I3Particle muon;
  muon.SetPos(10,0,0);
  muon.SetDir(90*deg,0); // muon moving toward -x axis
  muon.SetShape(I3Particle::InfiniteTrack);
  return muon;
}

static I3Particle starttrack()
{
  I3Particle starttrack;
  starttrack.SetPos(1,1,1);
  starttrack.SetDir(0,0);
  starttrack.SetTime(100);
  starttrack.SetShape(I3Particle::StartingTrack);
  return starttrack;
}

static I3Particle casc1()
{
  I3Particle casc1;
  casc1.SetPos(2,2,2);
  casc1.SetTime(100);
  casc1.SetShape(I3Particle::Cascade);
  return casc1;
}

static I3Particle casc2()
{
  I3Particle casc2;
  casc2.SetPos(2,2,7);
  casc2.SetShape(I3Particle::Cascade);
  return casc2;
}

static I3Position p(1,1,1);
static I3Position q(2,2,2);
static I3Position r(0,0,0);
static I3Position a1;


void TRAFO(double *Xdir, double trafo[3][3]);


TEST_GROUP(I3Calculator)

TEST(ShiftAlongTrack)
{
  I3Position n = inftrack().ShiftAlongTrack(sqrt(2.));

  ENSURE_DISTANCE(n.GetX(),0.,0.0001);
  ENSURE_DISTANCE(n.GetY(),1.,0.0001);
  ENSURE_DISTANCE(n.GetZ(),1.,0.0001);

  ENSURE_DISTANCE(muon().ShiftAlongTrack(15).GetX(),-5.,0.0001);
}

TEST(IsOnTrack)
{
  I3Position on(2,0.09*m,0);
  ENSURE(IsOnTrack(muon(),on,0.1*m));

  I3Position n = inftrack().ShiftAlongTrack(2.38);
  ENSURE(IsOnTrack(inftrack(),n,0.1*m));

  ENSURE(!IsOnTrack(starttrack(),on,0.1*m));

  on.SetPosition(1,1,1.1);
  ENSURE(!IsOnTrack(starttrack(),on,0.1*m));
}

TEST(ClosestApproachDistance)
{
  ENSURE_DISTANCE(ClosestApproachDistance(inftrack(),p),1.,0.0001);

  ENSURE_DISTANCE(ClosestApproachDistance(starttrack(),q),sqrt(3.),0.0001);

  a1.SetPosition(1,0,-7);
  ENSURE_DISTANCE(ClosestApproachDistance(starttrack(),a1),1.,0.0001);

  a1.SetPosition(1,1,0);
  ENSURE_DISTANCE(ClosestApproachDistance(starttrack(),a1),0.,0.0001);

  a1.SetPosition(1,1,2);
  ENSURE_DISTANCE(ClosestApproachDistance(starttrack(),a1),1.,0.0001);

  a1.SetPosition(1,0,2);
  ENSURE_DISTANCE(ClosestApproachDistance(starttrack(),a1),sqrt(2.0),0.0001);
}

TEST(CherenkovPosition)
{ 
  a1.SetPosition(1,0,-1);
  I3Position pos = CherenkovPosition(starttrack(),a1);
  ENSURE_DISTANCE(pos.GetZ(),0.1616288,0.0001);

  a1.SetPosition(-2,1,0);
  pos = CherenkovPosition(muon(),a1);
  ENSURE_DISTANCE(pos.GetX(),-0.838371,0.0001);
}

TEST(CherenkovTime)
{ 
  a1.SetPosition(0,0,0);
  ENSURE(isnan(CherenkovTime(starttrack(),a1)));

  a1.SetPosition(1,0,-1);
  ENSURE_DISTANCE(CherenkovTime(starttrack(),a1)/ns,9.731156,0.0001);

  a1.SetPosition(1,0,-11);
  ENSURE_DISTANCE(CherenkovTime(starttrack(),a1)/ns,43.08756,0.0001);

  a1.SetPosition(-2,1,0);
  ENSURE_DISTANCE(CherenkovTime(muon(),a1)/ns,43.08756,0.0001);
}

TEST(CherenkovDistance)
{
  a1.SetPosition(1,0,0);
  ENSURE(isnan(CherenkovDistance(starttrack(),a1)));

  a1.SetPosition(1,0,-1);
  ENSURE_DISTANCE(CherenkovDistance(starttrack(),a1),1.532769,0.0001);

  a1.SetPosition(1,0,-11);
  ENSURE_DISTANCE(CherenkovDistance(starttrack(),a1),1.532769,0.0001);

  a1.SetPosition(-2,1,0);
  ENSURE_DISTANCE(CherenkovDistance(muon(),a1),1.532769,0.0001);

  ENSURE_DISTANCE(CherenkovDistance(muon(),q),4.33532,0.0001);
}

TEST(CherenkovAngle)
{ 
  a1.SetPosition(0,1,0);
  ENSURE_DISTANCE(CherenkovApproachAngle(muon(),a1)/deg,90.0,0.0001);

  a1.SetPosition(0,0,1);
  ENSURE_DISTANCE(CherenkovApproachAngle(muon(),a1)/deg,49.2761,0.0001);

  ENSURE_DISTANCE(CherenkovApproachAngle(muon(),p,I3OMGeo::Up)/deg,117.47272,0.0001);
}

TEST(CascadeDistance)
{ 
  ENSURE_DISTANCE(CherenkovDistance(casc1(),r), 3.46410, 0.0001);
}

TEST(CascadeTime)
{
  ENSURE_DISTANCE(CherenkovTime(casc1(),r)/ns, 15.6725, 0.001);
}

TEST(TimeResidual_track)
{
  a1.SetPosition(0,0,-4);
  ENSURE_DISTANCE(TimeResidual(starttrack(),a1,120), -1.0055, 0.0001);
}

TEST(TimeResidual_cascade)
{
  ENSURE_DISTANCE(TimeResidual(casc1(),r,120), 4.32749, 0.0001);
}

TEST(Angle)
{
  ENSURE_DISTANCE(Angle(inftrack(),muon())/deg,90.,0.001);
    
  I3Particle track1(I3Particle::InfiniteTrack);
  track1.SetDir(0,1,-1);
  I3Particle track2(I3Particle::InfiniteTrack);
  track2.SetDir(1,0,-1);

  ENSURE_DISTANCE(Angle(track1,track2)/deg,60.,0.001);
}

TEST(Distance)
{ 
  ENSURE_DISTANCE(Distance(casc1(),casc2()),5.0,0.0001);
}


TEST(garbage)
{
  try
    {
      I3Particle particle;
      I3Position position;
      I3Position chpos;
      double chtime;
      double chdist;
      double chapangle;

      CherenkovCalc(particle,
		    position,
		    chpos,
		    chtime,
		    chdist,
		    chapangle);

      ENSURE(0,"That should have thrown");
    }
  catch(const exception& e)
    {
      // that should have thrown 'cause the particle shape wasn't set
    }
}

TEST(JAMS_time_residual)
{
  I3Particle track;
  track.SetTime(0);
  track.SetPos(0,0,0);
  track.SetDir(0,1,-1);
  track.SetShape(I3Particle::InfiniteTrack);
  double TG_CER = tan(acos(1./I3Constants::n_ice));
  I3Position pos(0,1,-10);
  double time(10);

  //--Calculate dt,rho from phys-services, SIMPLEST WAY
  double rho = ClosestApproachDistance(track, pos);
  double dt = TimeResidual(track, pos, time);

  //--Calculate dt,rho using phys-services, but break up calculation
  double rho_ = ClosestApproachDistance(track, pos);
  double l = DistanceAlongTrack(track,ClosestApproachPosition(track, pos));
  double dt_ = time - track.GetTime() - (l)/I3Constants::c
    - rho_*TG_CER/I3Constants::c;

  //--Calculate dt,rho Peter's way, but using phys-services
  I3Position p1 = InTrackSystem(track, pos);
  double rho1 = p1.GetRho();
  double Z = p1.GetZ() - track.GetZ();
  double dt1 = time - track.GetTime() - ( Z + rho1*TG_CER ) / I3Constants::c;

  //--Calculate dt,rho Peter's way from code, using TRAFO
  double dir[3];
  dir[0] = track.GetDir().GetX();
  dir[1] = track.GetDir().GetY();
  dir[2] = track.GetDir().GetZ();
  double trafo[3][3];
  TRAFO(dir, trafo);
  double Tom   = time - track.GetTime();
  double Xom   = pos.GetX() - track.GetX();
  double Yom   = pos.GetY() - track.GetY();
  double Zom   = pos.GetZ() - track.GetZ();
  double XX    = Xom * trafo[0][0] + Yom * trafo[1][0] + Zom * trafo[2][0];
  double YY    = Xom * trafo[0][1] + Yom * trafo[1][1] + Zom * trafo[2][1];
  double ZZ    = Xom * trafo[0][2] + Yom * trafo[1][2] + Zom * trafo[2][2];
  double rho2   = sqrt(XX*XX + YY*YY);
  double dt2    = Tom - (ZZ + rho2*TG_CER)/I3Constants::c;

  //--Compare the different ways of calculation
  double RHO = 4.5*sqrt(2.);
  double DT = -35.4181;
  double PERC = 0.001;

  ENSURE_DISTANCE(rho,  RHO, abs(RHO*PERC));
  ENSURE_DISTANCE(rho_, RHO, abs(RHO*PERC));
  ENSURE_DISTANCE(rho1, RHO, abs(RHO*PERC));
  ENSURE_DISTANCE(rho2, RHO, abs(RHO*PERC));

  ENSURE_DISTANCE(dt,  DT, abs(DT*PERC));
  ENSURE_DISTANCE(dt_, DT, abs(DT*PERC));
  ENSURE_DISTANCE(dt1, DT, abs(DT*PERC));
  ENSURE_DISTANCE(dt2, DT, abs(DT*PERC));
}


TEST(JAMS_time_residual_many)
{
  double TG_CER = tan(acos(1./I3Constants::n_ice));
  I3Particle track;
  track.SetShape(I3Particle::InfiniteTrack);
  track.SetTime(0);
  track.SetPos(0,0,0);

  for (int i=1; i<10; i++) {
    double zen = 180*deg/10 * (double)i;
    double azi = 360*deg/10 * (double)i;
    track.SetDir(zen, azi);
    double time(10);

    // vary x,y,z of the OM from -120 to +120...
    for (int j1=-3; j1<3; j1++,j1++) {
      for (int j2=-3; j2<3; j2++,j2++) {
	for (int j3=-3; j3<3; j3++,j3++) {
	  I3Position pos(40.*(double)j1, 40.*(double)j2, 40.*(double)j3);

    //--Calculate dt,rho from phys-services, SIMPLEST WAY
    double rho = ClosestApproachDistance(track, pos);
    double dt = TimeResidual(track, pos, time, n_ice, n_ice);

    //--Calculate dt,rho using phys-services, but break up calculation
    double rho_ = ClosestApproachDistance(track, pos);
    double l = DistanceAlongTrack(track,ClosestApproachPosition(track, pos));
    double dt_ = time - track.GetTime() - (l)/I3Constants::c
      - rho_*TG_CER/I3Constants::c;

    //--Calculate dt,rho Peter's way, but using phys-services
    I3Position p1 = InTrackSystem(track, pos);
    double rho1 = p1.GetRho();
    double Z = p1.GetZ() - track.GetZ();
    double dt1 = time - track.GetTime() - ( Z + rho1*TG_CER ) / I3Constants::c;

    //--Calculate dt,rho Peter's way from code, using TRAFO
    double dir[3];
    dir[0] = track.GetDir().GetX();
    dir[1] = track.GetDir().GetY();
    dir[2] = track.GetDir().GetZ();
    double trafo[3][3];
    TRAFO(dir, trafo);
    double Tom   = time - track.GetTime();
    double Xom   = pos.GetX() - track.GetX();
    double Yom   = pos.GetY() - track.GetY();
    double Zom   = pos.GetZ() - track.GetZ();
    double XX    = Xom * trafo[0][0] + Yom * trafo[1][0] + Zom * trafo[2][0];
    double YY    = Xom * trafo[0][1] + Yom * trafo[1][1] + Zom * trafo[2][1];
    double ZZ    = Xom * trafo[0][2] + Yom * trafo[1][2] + Zom * trafo[2][2];
    double rho2   = sqrt(XX*XX + YY*YY);
    double dt2    = Tom - (ZZ + rho2*TG_CER)/I3Constants::c;

      cout<<track.GetDir().GetX()<<" "<<track.GetDir().GetY()<<" "
      <<track.GetDir().GetZ()<<" "<<endl;//###
      cout<<time<<" "<<l/I3Constants::c<<" "<<rho_*TG_CER/I3Constants::c<<endl;
      cout<<time<<" "<<Z/I3Constants::c<<" "<<rho1*TG_CER/I3Constants::c<<endl;
      cout<<Tom<<" "<<ZZ/I3Constants::c<<" "<<rho2*TG_CER/I3Constants::c<<endl;
      cout<<track.GetDir().CalcTheta()/I3Units::deg<<endl;
      cout<<track.GetDir().CalcPhi()/I3Units::deg<<endl;
      cout<<"...  "<<dt<<"   "<<rho<<"   "<<dt-rho<<endl;
      cout<<"---  "<<dt_<<"   "<<rho_<<"   "<<dt_-rho_<<endl;
      cout<<"===  "<<dt1<<"   "<<rho1<<"   "<<dt1-rho1<<endl;
      cout<<"###  "<<dt2<<"   "<<rho2<<"   "<<dt2-rho2<<endl;

      //--Compare the different ways of calculation
      double PREC = 0.0001;
      ENSURE_DISTANCE(rho,  rho, abs(rho*PREC));
      ENSURE_DISTANCE(rho_, rho, abs(rho*PREC));
      ENSURE_DISTANCE(rho1, rho, abs(rho*PREC));
      ENSURE_DISTANCE(rho2, rho, abs(rho*PREC));
      
      ENSURE_DISTANCE(dt,  dt, abs(dt*PREC));
      ENSURE_DISTANCE(dt_, dt, abs(dt*PREC));
      ENSURE_DISTANCE(dt1, dt, abs(dt*PREC));
      ENSURE_DISTANCE(dt2, dt, abs(dt*PREC));
	}
      }
    }
  }
}


// from Peter Steffen's JAMS code (in amajams)
//-----------------------------------------
void TRAFO ( double Xdir[3] , double trafo[3][3] ) {
  double DXx,DXy,DXz, DYx,DYy,DYz, DZx,DZy,DZz, Norm;

/*                                            |  Z-axis = track dir.   |*/
  DZx    = Xdir[0];
  DZy    = Xdir[1];
  DZz    = Xdir[2];

  if(DZx*DZx + DZy*DZy < 1.e-10) {
    DXx    = 1.;
    DXy    = 0.;
    DXz    = 0.;
    DYx    = 0.;
    DYy    = 1.;
    DYz    = 0.;
    DZx    = 0.;
    DZy    = 0.;
    DZz    = 1.;
  }

  else{
/*                                            |  X: transvers Z-axis   |*/
    DXx    =  DZy;
    DXy    = -DZx;
    DXz    =  .0;
    Norm   = sqrt(DXx*DXx + DXy*DXy);
    DXx    =  DXx / Norm;
    DXy    =  DXy / Norm;

/*                                            |  Y-axis                |*/
    DYx    =  DZy*DXz - DZz*DXy;
    DYy    =  DZz*DXx - DZx*DXz;
    DYz    =  DZx*DXy - DZy*DXx;
    Norm   = sqrt(DYx*DYx + DYy*DYy + DYz*DYz);
    DYx    =  DYx / Norm;
    DYy    =  DYy / Norm;
    DYz    =  DYz / Norm;

  }

  trafo[0][0] = DXx;
  trafo[1][0] = DXy;
  trafo[2][0] = DXz;
  trafo[0][1] = DYx;
  trafo[1][1] = DYy;
  trafo[2][1] = DYz;
  trafo[0][2] = DZx;
  trafo[1][2] = DZy;
  trafo[2][2] = DZz;

  return;
}
