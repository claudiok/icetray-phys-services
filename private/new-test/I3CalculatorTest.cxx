/**
    copyright  (C) 2004
    the icecube collaboration
    $Id$

    @version $Revision: 1.2 $
    @date $Date$
    @author dule

    @todo
*/

#include <I3Test.h>

#include "phys-services/I3Calculator.h"
#include "dataclasses/I3BasicTrack.h"
#include "dataclasses/I3BasicCascade.h"
#include "dataclasses/I3DirectionalCascade.h"
#include "dataclasses/I3Position.h"
#include "dataclasses/I3Direction.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
using std::string;
using std::cout;
using std::endl;
using namespace I3Units;

#include "dataclasses/I3Starting.h"
#include "dataclasses/I3NonEnergetic.h"
#include "dataclasses/I3Composite.h"
typedef I3TrackImpl<I3Starting, I3NonEnergetic, I3Composite> I3StartingTrack;
typedef shared_ptr<I3StartingTrack> I3StartingTrackPtr;

using namespace I3Calculator;

static I3BasicTrackPtr inftrack()
{
  I3BasicTrackPtr inftrack (new I3BasicTrack);
  inftrack->SetPos(0,0,0);
  inftrack->SetDir(0,1,1);
  return inftrack;
}

static I3BasicTrackPtr muon()
{
  I3BasicTrackPtr muon (new I3BasicTrack);
  muon->SetPos(10,0,0);
  muon->SetDir(90*deg,0); // muon moving toward -x axis
  return muon;
}

static I3StartingTrackPtr starttrack()
{
  I3StartingTrackPtr starttrack (new I3StartingTrack);
  starttrack->SetStartPos(1,1,1);
  starttrack->SetDir(0,0);
  return starttrack;
}

static I3Position p(1,1,1);
static I3Position q(2,2,2);
static I3Position r(0,0,0);
static I3Position a1;


TEST_GROUP(I3Calculator)

TEST(ShiftAlongTrack)
{
  I3Position n = ShiftAlongTrack(inftrack(),sqrt(2.));

  ENSURE_DISTANCE(n.GetX(),0.,0.0001);
  ENSURE_DISTANCE(n.GetY(),1.,0.0001);
  ENSURE_DISTANCE(n.GetZ(),1.,0.0001);

  ENSURE_DISTANCE(ShiftAlongTrack(muon(),15).GetX(),-5.,0.0001);
}

TEST(IsOnTrack)
{
  I3Position on(2,0.09*m,0);
  ENSURE(IsOnTrack(muon(),on,0.1*m));

  I3Position n = ShiftAlongTrack(inftrack(),2.38);
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

TEST(CherenkovAngle)
{ 
  a1.SetPosition(0,1,0);
  ENSURE_DISTANCE(CherenkovAngle(muon(),a1)/deg,90.0,0.0001);

  a1.SetPosition(0,0,1);
  ENSURE_DISTANCE(CherenkovAngle(muon(),a1)/deg,49.7612,0.0001);

  ENSURE_DISTANCE(CherenkovAngle(muon(),p,I3OMGeo::Up)/deg,117.179,0.0001);
}

TEST(CascadeDistance)
{ 
  I3BasicCascadePtr casc (new I3BasicCascade);
  casc->SetPos(2,2,2);
  I3BasicCascadePtr casc2 (new I3BasicCascade);
  casc2->SetPos(2,2,7);

  ENSURE_DISTANCE(CascadeDistance(casc,r),3.46410,0.0001);

  ENSURE_DISTANCE(CascadeDistance(casc,casc2),5.0,0.0001);
}

TEST(CascadeTime)
{
  I3BasicCascadePtr casc (new I3BasicCascade);
  casc->SetPos(2,2,2);

  ENSURE_DISTANCE(CascadeTime(casc,r)/ns,15.137,0.001);
}

TEST(AngleDiff)
{
  ENSURE_DISTANCE(AngleDiff(inftrack(),muon())/deg,90.,0.001);
    
  I3BasicTrackPtr track1 (new I3BasicTrack);
  track1->SetDir(0,1,-1);
  I3BasicTrackPtr track2 (new I3BasicTrack);
  track2->SetDir(1,0,-1);

  ENSURE_DISTANCE(AngleDiff(track1,track2)/deg,60.,0.001);
}
