/**
    copyright  (C) 2004
    the icecube collaboration
    $Id: I3CalculatorTest.cxx,v 1.1 2005/04/13 14:16:05 dule Exp $

    @version $Revision: 1.1 $
    @date $Date: 2005/04/13 14:16:05 $
    @author dule

    @todo
*/

#include <icetray/test/I3Test.h>

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
typedef I3TrackImpl<I3Starting, I3NonEnergetic, I3Composite> I3StartingMuon;
typedef PtrPolicy<I3StartingMuon>::ThePolicy I3StartingMuonPtr;

using namespace I3Calculator;

TEST_GROUP(I3Calculator);

TEST(I3Calculator)
{ 
	cout <<"Creating I3Position p,q,r..."<<endl;
	I3Position p(1,1,1);
	I3Position q(2,2,2);
	I3Position r(0,0,0);
	q.ToStream(cout);//#####

    cout <<"Creating I3Direction d,e..."<<endl;
    I3Direction d(0,0); // direction straight down -- zenith=0 ==> theta=180
    I3Direction e(0,1,1); // direction along y-z plane, at 45 deg

    cout <<"Creating Infinite track..."<<endl;
    I3BasicTrackPtr track_inf (new I3BasicTrack);
    I3TrackPtr inftrackptr = boost::dynamic_pointer_cast<I3Track>(track_inf);
    track_inf->SetPos(r);
    track_inf->SetDir(e);
    track_inf->SetT(10);

    cout <<"Creating Starting track..."<<endl;
    I3StartingMuonPtr track_start (new I3StartingMuon);
    I3TrackPtr starttrackptr=boost::dynamic_pointer_cast<I3Track>(track_start);
    track_start->SetStartPos(p);
    track_start->SetDir(d);
    track_start->SetStartT(10);

    cout <<"Creating BasiMuon"<<endl;
    I3BasicTrackPtr muon (new I3BasicTrack);
    I3TrackPtr muonptr = boost::dynamic_pointer_cast<I3Track>(muon);
    muon->SetPos(10,0,0);
    muon->SetDir(90*deg,0); // muon moving toward -x axis

    cout <<"Creating a cascade..."<<endl;
    I3BasicCascadePtr casc_bas (new I3BasicCascade);
    I3CascadePtr cascptr = boost::dynamic_pointer_cast<I3Cascade>(casc_bas);
    casc_bas->SetPos(q);

    cout <<"Creating a directional cascade..."<<endl;
    I3DirectionalCascadePtr casc_dir (new I3DirectionalCascade);
    casc_dir->SetPos(0,0,4);

    cout <<"Distance..."<<endl; //-------------------------

    //cout <<" distance starttrack-pos: "<<Distance(starttrackptr,r)<<endl;
    ENSURE_DISTANCE(Distance(starttrackptr,r),2.7320508,0.0001);

    //cout <<" distance casc-pos: "<<Distance(cascptr,r)<<endl;
    ENSURE_DISTANCE(Distance(cascptr,r),3.46410,0.0001);
#if 0

    cout <<"StartDistance..."<<endl; //-------------------------

    cout <<" distance inftrack-pos: "<<StartDistance(inftrackptr,r)
			<<" <-- this should be nan!"<<endl;
    ENSURE("StartDistance(InfTrack,Pos) failed", 
			  isnan(StartDistance(inftrackptr,r)));

    cout <<"ShiftAlongTrack..."<<endl; //-------------------------

    I3Position n = ShiftAlongTrack(inftrackptr,sqrt(2.));
    cout<<n;
    ENSURE_DISTANCE("ShiftAlongTrack.X failed",n.GetX(),0.,0.0001);
    ENSURE_DISTANCE("ShiftAlongTrack.Y failed",n.GetY(),1.,0.0001);
    ENSURE_DISTANCE("ShiftAlongTrack.Z failed",n.GetZ(),1.,0.0001);

    ENSURE_DISTANCE("ShiftAlongTrack.X failed",
		    ShiftAlongTrack(muonptr,15).GetX(),-5.,0.0001);

    cout <<"IsOnTrack..."<<endl; //-------------------------

    I3Position on(2,0.09*m,0);
    ensure("IsOnTrack.muon/yes/ failed",IsOnTrack(muonptr,on,0.1*m));
    ensure("IsOnTrack.inf/yes/ failed",IsOnTrack(inftrackptr,n,0.1*m));
    ensure("IsOnTrack.1/no/ failed",!IsOnTrack(starttrackptr,on,0.1*m));
    on.SetPosition(1,1,1.1);
    ensure("IsOnTrack.2/no/ failed",!IsOnTrack(starttrackptr,on,0.1*m));

    cout <<"ClosestApproachDistance..."<<endl; //-------------------------

    I3Position a1;
    ENSURE_DISTANCE("ClosestApproachDistance(inftrack,p) failed",
		    ClosestApproachDistance(inftrackptr,p),1.,0.0001);
    ENSURE_DISTANCE("ClosestApproachDistance(starttrack,q) failed",
		    ClosestApproachDistance(starttrackptr,q),
		    sqrt(3.),0.0001);
    a1.SetPosition(1,0,-7);
    ENSURE_DISTANCE("ClosestApproachDistance(starttrack,[1,0,-7]) failed",
		    ClosestApproachDistance(starttrackptr,a1),1.,0.0001);
    a1.SetPosition(1,1,0);
    ENSURE_DISTANCE("ClosestApproachDistance(starttrack,[1,1,0]) failed",
		    ClosestApproachDistance(starttrackptr,a1),0.,0.0001);
    a1.SetPosition(1,1,2);
    ENSURE_DISTANCE("ClosestApproachDistance(starttrack,[1,1,2]) failed",
		    ClosestApproachDistance(starttrackptr,a1),1.,0.0001);
    a1.SetPosition(1,0,2);
    ENSURE_DISTANCE("ClosestApproachDistance(starttrack,[1,0,2]) failed",
		    ClosestApproachDistance(starttrackptr,a1),
		    sqrt(2.),0.0001);

    cout <<"CherenkovTime..."<<endl; //-------------------------

    a1.SetPosition(0,0,0);
    cout<<" cherenkov-time(start,[0,0,0]): "
		  <<CherenkovTime(starttrackptr,a1)/ns
		  <<" <-- this should be nan!"<<endl;
    ensure("CherenkovTime failed", isnan(CherenkovTime(starttrackptr,a1)));

    a1.SetPosition(1,0,-1);
    cout<<" cherenkov-time(start,[1,0,-1]): "
		  <<CherenkovTime(starttrackptr,a1)/ns<<endl;
    ENSURE_DISTANCE("CherenkovTime(starttrack,[1,0,-1]) failed",
		    CherenkovTime(starttrackptr,a1)/ns,9.49399,0.0001);

    a1.SetPosition(1,0,-11);
    cout<<" cherenkov-time(start,[1,0,-11]): "
		  <<CherenkovTime(starttrackptr,a1)/ns<<endl;
    ENSURE_DISTANCE("CherenkovTime(starttrack,[1,0,-11]) failed",
		    CherenkovTime(starttrackptr,a1)/ns,42.8504,0.0001);

    a1.SetPosition(-2,1,0);
    cout<<" cherenkov-time(muon,[-2,1,0]): "
		  <<CherenkovTime(muonptr,a1)/ns<<endl;
    ENSURE_DISTANCE("CherenkovTime(muon,[-2,1,0]) failed",
		    CherenkovTime(muonptr,a1)/ns,42.8504,0.0001);

    cout <<"CherenkovDistance..."<<endl; //-------------------------

    a1.SetPosition(1,0,0);
    cout<<" cherenkov-distance(start,[0,0,0]): "
		  <<CherenkovDistance(starttrackptr,a1)
		  <<" <-- this should be nan!"<<endl;
    ensure("CherenkovDistance(starttrack,[0,0,0]) failed", isnan(CherenkovDistance(starttrackptr,a1)));

    a1.SetPosition(1,0,-1);
    cout<<" cherenkov-distance(start,[1,0,-1]): "
		  <<CherenkovDistance(starttrackptr,a1)<<endl;
    ENSURE_DISTANCE("CherenkovDistance(starttrack,[1,0,-1]) failed",
		   CherenkovDistance(starttrackptr,a1),1.54805,0.0001);

    a1.SetPosition(1,0,-11);
    cout<<" cherenkov-distance(start,[1,0,-11]): "
		  <<CherenkovDistance(starttrackptr,a1)<<endl;
    ENSURE_DISTANCE("CherenkovDistance(starttrack,[1,0,-11]) failed",
		   CherenkovDistance(starttrackptr,a1),1.54805,0.0001);

    a1.SetPosition(-2,1,0);
    cout<<" cherenkov-distance(muon,[-2,1,0]): "
		  <<CherenkovDistance(muonptr,a1)<<endl;
    ENSURE_DISTANCE("CherenkovDistance(muon,[-2,1,0]) failed",
		    CherenkovDistance(muonptr,a1),1.54805,0.0001);

    cout<<" cherenkov-distance(muon,[2,2,2]): "
		  <<CherenkovDistance(muonptr,q)<<endl;
    ENSURE_DISTANCE("CherenkovDistance(muon,[2,2,2]) failed",
		    CherenkovDistance(muonptr,q),4.37854,0.0001);

    cout <<"CherenkovAngle..."<<endl; //-------------------------

    a1.SetPosition(0,1,0);
    cout<<" cherenkov-angle(muon,[0,1,0]): "
		  <<CherenkovAngle(muonptr,a1)/deg<<endl;
    ENSURE_DISTANCE("CherenkovAngle(muon,[0,1,0]) failed",
		    CherenkovAngle(muonptr,a1)/deg,90.0,0.0001);

    a1.SetPosition(0,0,1);
    cout<<" cherenkov-angle(muon,[0,0,1]): "
		  <<CherenkovAngle(muonptr,a1)/deg<<endl;
    ENSURE_DISTANCE("CherenkovAngle(muon,[0,0,1]) failed",
		    CherenkovAngle(muonptr,a1)/deg,49.7612,0.0001);

    cout<<" cherenkov-angle(muon,[1,1,1]): "
		  <<CherenkovAngle(muonptr,p,I3OMGeo::Up)/deg<<endl;
    ENSURE_DISTANCE("CherenkovAngle(muon,[1,1,1]) failed",
		    CherenkovAngle(muonptr,p,I3OMGeo::Up)/deg,
		    117.179,0.0001);

    cout <<"CascadeTime..."<<endl; //-------------------------

    cout<<" cascade-time(cascade,[0,0,0]): "<<CascadeTime(cascptr,r)/ns<<endl;
    ENSURE_DISTANCE("CascadeTime(cascade,[0,0,0]) failed",
		    CascadeTime(cascptr,r)/ns,15.137,0.001);

    cout <<"CascadeDistance..."<<endl; //-------------------------

    cout<<" cascade-distance(cascade,[0,0,0]): "
		  <<CascadeDistance(casc_dir,r)<<endl;
    ENSURE_DISTANCE("CascadeDistance(directional-cascade,[0,0,0]) failed",
		    CascadeDistance(casc_dir,r),4.,0.001);

    cout <<"AngleDiff..."<<endl; //-------------------------

    cout<<" angle-diff(track_inf,muon): "<<AngleDiff(track_inf,muon)/deg<<endl;
    ENSURE_DISTANCE("AngleDiff(track_inf,muon) failed",
						  AngleDiff(track_inf,muon)/deg,90.,0.001);
    
    I3BasicTrackPtr track1 (new I3BasicTrack);
    track1->SetDir(0,1,-1);
    I3BasicTrackPtr track2 (new I3BasicTrack);
    track2->SetDir(1,0,-1);
    cout<<" angle-diff(track1[0,1,-1],track2[1,0,-1]): "
		  <<AngleDiff(track1,track2)/deg<<endl;
    ENSURE_DISTANCE("AngleDiff(track1[0,1,-1],track2[1,0,-1] failed",
		    AngleDiff(track1,track2)/deg,60.,0.001);
#endif
}
