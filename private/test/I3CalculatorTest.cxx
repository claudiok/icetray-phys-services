/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3CalculatorTest.cxx,v 1.1 2004/09/14 00:58:33 dule Exp $

    @version $Revision: 1.1 $
    @date $Date: 2004/09/14 00:58:33 $
    @author pretz

    @todo
*/

#include "TUT/tut.h"

#include "phys-services/I3CalculatorImpl.h"
#include "dataclasses/I3BasicMuon.h"
#include "dataclasses/I3StartingMuon.h"
#include "dataclasses/I3BasicCascade.h"
#include "dataclasses/I3Position.h"
#include "dataclasses/I3Direction.h"
#include "TFile.h"
#include "TTree.h"
#include <string>
using std::string;
using std::cout;
using std::endl;
using namespace I3Units;

namespace tut
{
  struct I3CalculatorTest
  {
  };

  typedef test_group<I3CalculatorTest> factory;
  typedef factory::object object;
}

namespace
{
  tut::factory t("I3CalculatorTest");
}

namespace tut
{ 

  /**
   * Make sure that the changing of coordinate systems works well
   */
  void object::test<1>(){
    Double_t pi = 3.14159265358979323846;

    cout <<"Creating I3Position p,q,r..."<<endl;
    I3Position p(1,1,1);
    I3Position q(2,2,2);
    I3Position r(0,0,0);

    cout <<"Creating I3Direction d,e..."<<endl;
    I3Direction d(0,0); // direction straight down -- zenith=0 ==> theta=180
    I3Direction e(0,1,1); // direction along y-z plane, at 45 deg

    cout <<"Creating Infinite and Starting tracks..."<<endl;
    I3BasicMuonPtr track_inf (new I3BasicMuon);
    I3StartingMuonPtr track_start (new I3StartingMuon);

    cout <<"Creating a cascade..."<<endl;
    I3BasicCascadePtr casc_bas (new I3BasicCascade);

    cout <<"Setting values for track_start..."<<endl;
    track_start->SetStartPos(p);
    track_start->SetDir(d);
    track_start->SetStartT(10);

    cout <<"Setting values for track_inf..."<<endl;
    track_inf->SetPos(r);
    track_inf->SetDir(e);
    track_inf->SetT(10);

    cout <<"Setting values for casc_bas..."<<endl;
    casc_bas->SetPos(q);
    
    cout <<"Creating a new I3Calculator object..."<<endl;
    I3CalculatorImpl calc;

    cout <<"Distance..."<<endl; //-------------------------

    I3TrackPtr starttrackptr = 
      roost::dynamic_pointer_cast<I3Track>(track_start);
    cout <<" distance starttrack-pos: "<<calc.Distance(starttrackptr,r)<<endl;
    ensure_distance("Distance(StartTrack,Pos) failed",
		    calc.Distance(starttrackptr,r),1.7320508,0.0001);

    I3CascadePtr cascptr = roost::dynamic_pointer_cast<I3Cascade>(casc_bas);
    cout <<" distance casc-pos: "<<calc.Distance(cascptr,r)<<endl;
    ensure_distance("Distance(Casc,Pos) failed",
		    calc.Distance(cascptr,r),3.46410,0.0001);

    cout <<"StartDistance..."<<endl; //-------------------------

    I3TrackPtr inftrackptr = roost::dynamic_pointer_cast<I3Track>(track_inf);
    cout <<" distance inftrack-pos: "<<calc.StartDistance(inftrackptr,r)<<
      " <-- this should be NAN!"<<endl;
    ensure_distance("StartDistance(InfTrack,Pos) failed",
		    calc.StartDistance(inftrackptr,r),0.0,0.0001);

    cout <<"ShiftAlongTrack..."<<endl; //-------------------------

    I3Position n = calc.ShiftAlongTrack(inftrackptr,sqrt(2.));
    cout<<n;
    ensure_distance("ShiftAlongTrack.X failed",n.GetX(),0.,0.0001);
    ensure_distance("ShiftAlongTrack.Y failed",n.GetY(),1.,0.0001);
    ensure_distance("ShiftAlongTrack.Z failed",n.GetZ(),1.,0.0001);

    I3BasicMuonPtr muon (new I3BasicMuon);
    I3TrackPtr muonptr = roost::dynamic_pointer_cast<I3Track>(muon);
    muon->SetPos(10,0,0);
    muon->SetDir(90*deg,0); // muon moving toward -x axis
    ensure_distance("ShiftAlongTrack.X failed",
		    calc.ShiftAlongTrack(muonptr,15).GetX(),-5.,0.0001);

    cout <<"IsOnTrack..."<<endl; //-------------------------

    I3Position on(2,0.09*m,0);
    ensure("IsOnTrack/yes/ failed",calc.IsOnTrack(muonptr,on,0.1*m));
    ensure("IsOnTrack/yes/ failed",calc.IsOnTrack(inftrackptr,n,0.1*m));
    ensure("IsOnTrack/no/ failed",!calc.IsOnTrack(starttrackptr,on,0.1*m));

    cout <<"ClosestApproachDistance..."<<endl; //-------------------------

    I3Position a1;
    ensure_distance("ClosestApproachDistance(inftrack,p) failed",
		    calc.ClosestApproachDistance(inftrackptr,p),1.,0.0001);
    ensure_distance("ClosestApproachDistance(starttrack,q) failed",
		    calc.ClosestApproachDistance(starttrackptr,q),
		    sqrt(3.),0.0001);
    a1.SetPosition(1,0,-7);
    ensure_distance("ClosestApproachDistance(starttrack,[1,0,-7]) failed",
		    calc.ClosestApproachDistance(starttrackptr,a1),1.,0.0001);
    a1.SetPosition(1,1,0);
    ensure_distance("ClosestApproachDistance(starttrack,[1,1,0]) failed",
		    calc.ClosestApproachDistance(starttrackptr,a1),0.,0.0001);
    a1.SetPosition(1,1,2);
    ensure_distance("ClosestApproachDistance(starttrack,[1,1,2]) failed",
		    calc.ClosestApproachDistance(starttrackptr,a1),1.,0.0001);
    a1.SetPosition(1,0,2);
    ensure_distance("ClosestApproachDistance(starttrack,[1,0,2]) failed",
		    calc.ClosestApproachDistance(starttrackptr,a1),
		    sqrt(2.),0.0001);

    cout <<"CherenkovTime..."<<endl; //-------------------------

    a1.SetPosition(0,0,0);
    cout<<" cherenkov-time(start,[0,0,0]): "
	<<calc.CherenkovTime(starttrackptr,a1)/ns
	<<" <-- this should be nan!"<<endl;
    //ensure_equals("CherenkovTime failed",
    //calc.CherenkovTime(starttrackptr,a1),NAN);

    a1.SetPosition(1,0,-1);
    cout<<" cherenkov-time(start,[1,0,-1]): "
	<<calc.CherenkovTime(starttrackptr,a1)/ns<<endl;
    ensure_distance("CherenkovTime(starttrack,[1,0,-1]) failed",
		    calc.CherenkovTime(starttrackptr,a1)/ns,9.49399,0.0001);

    a1.SetPosition(1,0,-11);
    cout<<" cherenkov-time(start,[1,0,-11]): "
	<<calc.CherenkovTime(starttrackptr,a1)/ns<<endl;
    ensure_distance("CherenkovTime(starttrack,[1,0,-11]) failed",
		    calc.CherenkovTime(starttrackptr,a1)/ns,42.8504,0.0001);

    a1.SetPosition(-2,1,0);
    cout<<" cherenkov-time(muon,[-2,1,0]): "
	<<calc.CherenkovTime(muonptr,a1)/ns<<endl;
    ensure_distance("CherenkovTime(muon,[-2,1,0]) failed",
		    calc.CherenkovTime(muonptr,a1)/ns,42.8504,0.0001);

  }
}
