#include <icetray/test/serialization-test.h>
//#include <icetray/test/I3Test.h>

#include "phys-services/I3Calculator.h"
#include "dataclasses/I3BasicTrack.h"
#include "dataclasses/I3Position.h"

using namespace I3Calculator;

TEST_GROUP(Cuts)

TEST(pos)
{
  cout<<endl;
  I3BasicTrackPtr track (new I3BasicTrack);
  track->SetPos(0,0,0);
  track->SetDir(0,0);
  double ang = 180*deg-acos(1/1.31);
  //ang = 135*deg;
  I3Position aa(10,ang,45*deg,I3Position::sph);
  I3Position bb(5,ang,-30*deg,I3Position::sph);
  I3Position cc(20,ang,45*deg,I3Position::sph);
  cc.ToStream(cout);//###
  cc.SetZ(cc.GetZ()-100);
  cc.ToStream(cout);//###
  I3Position dd(50,ang,180*deg,I3Position::sph);
  dd.ToStream(cout);//###
  dd.SetZ(dd.GetZ()+50);
  dd.ToStream(cout);//###
//   aa.ToStream(cout);
//   bb.ToStream(cout);
//   cc.ToStream(cout);
//   dd.ToStream(cout);
  double A = 1.31/(c*sin(acos(1/1.31)));
  double ta = sqrt(pow(aa.GetX(),2)+pow(aa.GetY(),2))*A + 7*ns;
  double tb = sqrt(pow(bb.GetX(),2)+pow(bb.GetY(),2))*A - 9*ns;
  double tc = sqrt(pow(cc.GetX(),2)+pow(cc.GetY(),2))*A + 5*ns;
  double td = sqrt(pow(dd.GetX(),2)+pow(dd.GetY(),2))*A - 3*ns;
  cout<<ta-CherenkovTime(track,aa)<<endl;
  cout<<tb-CherenkovTime(track,bb)<<endl;
  cout<<tc-(-100*1.31/c)-CherenkovTime(track,cc)<<" "<<sqrt(pow(aa.GetX(),2)+pow(aa.GetY(),2))<<" "<<track->GetPos().GetZ()<<endl;
  cout<<td-(50*1.31/c)-CherenkovTime(track,dd)<<endl;
}
