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
  ENSURE_DISTANCE(pos.GetZ(),0.181716,0.0001);

  a1.SetPosition(-2,1,0);
  pos = CherenkovPosition(muon(),a1);
  ENSURE_DISTANCE(pos.GetX(),-0.818284,0.0001);
}

TEST(CherenkovTime)
{ 
  a1.SetPosition(0,0,0);
  ENSURE(isnan(CherenkovTime(starttrack(),a1)));

  a1.SetPosition(1,0,-1);
  ENSURE_DISTANCE(CherenkovTime(starttrack(),a1)/ns,9.49399,0.0001);

  a1.SetPosition(1,0,-11);
  ENSURE_DISTANCE(CherenkovTime(starttrack(),a1)/ns,42.8504,0.0001);

  a1.SetPosition(-2,1,0);
  ENSURE_DISTANCE(CherenkovTime(muon(),a1)/ns,42.8504,0.0001);
}

TEST(CherenkovDistance)
{
  a1.SetPosition(1,0,0);
  ENSURE(isnan(CherenkovDistance(starttrack(),a1)));

  a1.SetPosition(1,0,-1);
  ENSURE_DISTANCE(CherenkovDistance(starttrack(),a1),1.54805,0.0001);

  a1.SetPosition(1,0,-11);
  ENSURE_DISTANCE(CherenkovDistance(starttrack(),a1),1.54805,0.0001);

  a1.SetPosition(-2,1,0);
  ENSURE_DISTANCE(CherenkovDistance(muon(),a1),1.54805,0.0001);

  ENSURE_DISTANCE(CherenkovDistance(muon(),q),4.37854,0.0001);
}

TEST(CherenkovAngle)
{ 
  a1.SetPosition(0,1,0);
  ENSURE_DISTANCE(CherenkovApproachAngle(muon(),a1)/deg,90.0,0.0001);

  a1.SetPosition(0,0,1);
  ENSURE_DISTANCE(CherenkovApproachAngle(muon(),a1)/deg,49.7612,0.0001);

  ENSURE_DISTANCE(CherenkovApproachAngle(muon(),p,I3OMGeo::Up)/deg,117.179,0.0001);
}

TEST(CascadeDistance)
{ 
  ENSURE_DISTANCE(CherenkovDistance(casc1(),r), 3.46410, 0.0001);
}

TEST(CascadeTime)
{
  ENSURE_DISTANCE(CherenkovTime(casc1(),r)/ns, 15.137, 0.001);
}

TEST(TimeResidual_track)
{
  a1.SetPosition(0,0,-3.66712);
  ENSURE_DISTANCE(TimeResidual(starttrack(),a1,120), 0.44025, 0.0001);
}

TEST(TimeResidual_cascade)
{
  ENSURE_DISTANCE(TimeResidual(casc1(),r,120), 4.86295, 0.0001);
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
      I3Position appos;
      double apdist;
      I3Position chpos;
      double chtime;
      double chdist;
      double chapangle;

      CherenkovCalc(particle,
		    position,
		    appos,
		    apdist,
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
