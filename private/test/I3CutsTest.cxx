#include <I3Test.h>

#include "phys-services/I3Calculator.h"
#include "phys-services/I3Cuts.h"
#include "dataclasses/I3BasicTrack.h"
#include "dataclasses/I3Position.h"
#include "dataclasses/I3Geometry.h"
#include "dataclasses/I3OMGeoIceCube.h"
#include "dataclasses/I3OMResponseMap.h"
#include "dataclasses/I3OMResponse.h"

using namespace I3Calculator;
using namespace I3Cuts;

I3Geometry CalcGeom(double size, vector<I3Position> pos)
{
  I3Geometry geometry;
  for (int i=0; i<size; i++) {
    OMKey om(1,i);
    geometry.GetInIceGeometry()[om] = 
      I3OMGeoIceCubePtr(new I3OMGeoIceCube);
    geometry.GetInIceGeometry()[om]->SetPos(pos[i]);
  }
  return geometry;
}

I3OMResponseMap CalcResp(double size, vector<double> time, string hitseries)
{
  I3OMResponseMap ommap;
  for (int i=0; i<size; i++) {
    OMKey om(1,i);
    ommap[om] = I3OMResponsePtr(new I3OMResponse);
    I3RecoHitSeriesDict& dict = ommap[om]->GetRecoHitSeriesDict();
    dict[hitseries] = I3RecoHitSeriesPtr(new I3RecoHitSeries);
    I3RecoHitSeriesPtr hits = dict[hitseries];
    hits->push_back(I3RecoHitPtr (new I3RecoHit));
    I3RecoHitPtr h = hits->back();
    h->SetTime(time[i]);
  }
  return ommap;
}

TEST_GROUP(I3Cuts)

TEST(FakeTrack)
{
  I3BasicTrackPtr track (new I3BasicTrack);
  track->SetPos(0,0,0);
  track->SetDir(0,0);
  double ang = 180*deg-acos(1/1.31);
  I3Position aa(10,ang,45*deg,I3Position::sph);
  I3Position bb(5,ang,-30*deg,I3Position::sph);
  I3Position cc(20,ang,45*deg,I3Position::sph); cc.SetZ(cc.GetZ()-100);
  I3Position dd(50,ang,180*deg,I3Position::sph); dd.SetZ(dd.GetZ()+50);
  double A = 1.31/(c*sin(acos(1/1.31)));
  double ta = sqrt(pow(aa.GetX(),2)+pow(aa.GetY(),2))*A + 7*ns;
  double tb = sqrt(pow(bb.GetX(),2)+pow(bb.GetY(),2))*A - 9*ns;
  double tc = 100/c + sqrt(pow(cc.GetX(),2)+pow(cc.GetY(),2))*A + 5*ns;
  double td = -50/c + sqrt(pow(dd.GetX(),2)+pow(dd.GetY(),2))*A - 3*ns;
  ENSURE_DISTANCE(CherenkovTime(track,aa)+7,ta,0.0001);
  ENSURE_DISTANCE(CherenkovTime(track,bb)-9,tb,0.0001);
  ENSURE_DISTANCE(CherenkovTime(track,cc)+5,tc,0.0001);
  ENSURE_DISTANCE(CherenkovTime(track,dd)-3,td,0.0001);
}

TEST(Ndir_DownTrack)
{
  I3BasicTrackPtr track (new I3BasicTrack);
  track->SetPos(0,0,0);
  track->SetDir(0,0);
  track->SetT(103.5);

  int size = 6;
  double r[] =   {10,   5, 20,   7,   10,  15};
  double phi[] = {45, -30, 15, 134,  100, -15};
  double z[] =   { 0,   0,  0, 100, -250, -50};
  double off[] = {17, -19,  5,  -3,   78,  50};

  double ang = 180*deg-acos(1/1.31);
  vector<I3Position> pos;
  double A = 1.31/(c*sin(acos(1/1.31)));
  vector<double> time;
  for (int i=0; i<size; i++) {
    I3Position p(r[i],ang,phi[i]*deg,I3Position::sph); p.SetZ(p.GetZ()-z[i]);
    pos.push_back(p);
    double t = (z[i]/c + sqrt(pow(pos[i].GetX(),2)+pow(pos[i].GetY(),2))*A
		+ track->GetT() + off[i]*ns);
    time.push_back(t);
    ENSURE_DISTANCE(CherenkovTime(track,pos[i])+off[i],
		    time[i]-track->GetT(), 0.0001,
		    "The time of this hit was somehow calculated wrong.");
  }

  string hitseries = "NdirTest";
  I3Geometry geometry = CalcGeom(size,pos);
  I3OMResponseMap ommap = CalcResp(size,time,hitseries);

  double ndir;
  ndir = Ndir(track,geometry,ommap,hitseries,-15.,25.);
  ENSURE_DISTANCE(ndir,3.,0.0001,
		  "Wrong number of direct hits calculated.");

  ndir = Ndir(track,geometry,ommap,hitseries,-15.,15.);
  ENSURE_DISTANCE(ndir,2.,0.0001,
		  "Wrong number of direct hits calculated.");

  ndir = Ndir(track,geometry,ommap,hitseries,-15.,75.);
  ENSURE_DISTANCE(ndir,4.,0.0001,
		  "Wrong number of direct hits calculated.");

  ndir = Ndir(track,geometry,ommap,hitseries,-15.,150.);
  ENSURE_DISTANCE(ndir,5.,0.0001,
		  "Wrong number of direct hits calculated.");
}

TEST(AllCuts_TiltedTrack)
{
  double ang = acos(1/1.31); // Cherenkov angle

  I3BasicTrackPtr track (new I3BasicTrack);
  track->SetPos(10,10,0);
  track->SetDir(180*deg-ang,90*deg);
  track->SetT(15);

  double size = 3;
  vector<I3Position> pos;
  I3Position p(10,10,20);  pos.push_back(p);
  p.SetPos(10,0,100);  pos.push_back(p);
  p.SetPos(10,50,0);  pos.push_back(p);

  vector<double> time;
  double t = 20*1.31/c + 15 + 17;  time.push_back(t);
  t = (10/sin(ang) + 1.31*(100-10/tan(ang)))/c + 15 - 9;  time.push_back(t);
  t = 40/c * (1.31/tan(ang) - 1/sin(ang)) + 15 + 3;  time.push_back(t);

  string hitseries = "NdirTest";
  I3Geometry geometry = CalcGeom(size,pos);
  I3OMResponseMap ommap = CalcResp(size,time,hitseries);
  double ndir = Ndir(track,geometry,ommap,hitseries,-15.,25.);
  ENSURE_DISTANCE(ndir,3.,0.0001,
		  "Wrong number of direct hits calculated.");

  double ldir = Ldir(track,geometry,ommap,hitseries,-15.,15.);
  ENSURE_DISTANCE(ldir,108.635,0.001,
		  "Wrong Ldir distance calculated.");

  double smooth = SmoothnessAll(track,geometry,ommap,hitseries);
  ENSURE_DISTANCE(smooth,0.121611,0.0001,
		 "Wrong smoothness calculated.");
}
