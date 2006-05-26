#include <I3Test.h>

#include "phys-services/I3Calculator.h"
#include "phys-services/I3Cuts.h"
#include "dataclasses/I3Position.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/geometry/I3Geometry.h"

using namespace I3Calculator;
using namespace I3Cuts;
using namespace I3Constants;

I3Geometry CalcGeom(vector<I3Position> pos)
{
  I3Geometry geometry;
  for (unsigned int i=0; i<pos.size(); i++) {
    OMKey om(1,i);
    I3OMGeo geo;
    geo.position.SetPos(pos[i]);
    geometry.omgeo[om] = geo;
  }
  return geometry;
}

I3RecoHitSeriesMap CalcHits(vector<double> time)
{
  I3RecoHitSeriesMap hitsmap;
  for (unsigned int i=0; i<time.size(); i++) {
    OMKey om(1,i);
    I3RecoHitSeries hits;
    I3RecoHit h;
    h.SetTime(time[i]);
    hits.push_back(h);
    hitsmap[om] = hits;
  }
  return hitsmap;
}


TEST_GROUP(I3Cuts)

TEST(FakeTrack)
{
  I3Particle track(I3Particle::InfiniteTrack);
  track.SetPos(0,0,0);
  track.SetDir(0,0);
  double ang = 180*deg-theta_cherenkov;
  I3Position aa(10,ang,45*deg,I3Position::sph);
  I3Position bb(5,ang,-30*deg,I3Position::sph);
  I3Position cc(20,ang,45*deg,I3Position::sph); cc.SetZ(cc.GetZ()-100);
  I3Position dd(50,ang,180*deg,I3Position::sph); dd.SetZ(dd.GetZ()+50);
  double A = 1./(c_ice*sin(theta_cherenkov));
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
  I3Particle track(I3Particle::InfiniteTrack);
  track.SetPos(0,0,0);
  track.SetDir(0,0);
  track.SetTime(103.5);

  int size = 6;
  double r[] =   {10,   5, 20,   7,   10,  15};
  double phi[] = {45, -30, 15, 134,  100, -15};
  double z[] =   { 0,   0,  0, 100, -250, -50};
  double off[] = {17, -19,  5,  -3,   78,  50};

  double ang = 180*deg-theta_cherenkov;
  vector<I3Position> pos;
  double A = 1./(c_ice*sin(theta_cherenkov));
  vector<double> time;
  for (int i=0; i<size; i++) {
    I3Position p(r[i],ang,phi[i]*deg,I3Position::sph); p.SetZ(p.GetZ()-z[i]);
    pos.push_back(p);
    double t = (z[i]/c + sqrt(pow(pos[i].GetX(),2)+pow(pos[i].GetY(),2))*A
		+ track.GetTime() + off[i]*ns);
    time.push_back(t);
    ENSURE_DISTANCE(CherenkovTime(track,pos[i])+off[i],
		    time[i]-track.GetTime(), 0.0001,
		    "The time of this hit was somehow calculated wrong.");
  }

  I3Geometry geometry = CalcGeom(pos);
  I3RecoHitSeriesMap hitsmap = CalcHits(time);

  double ndir;
  ndir = Ndir(track,geometry,hitsmap,-15.,25.);
  ENSURE_DISTANCE(ndir,3.,0.0001,
		  "Wrong number of direct hits calculated.");

  ndir = Ndir(track,geometry,hitsmap,-15.,15.);
  ENSURE_DISTANCE(ndir,2.,0.0001,
		  "Wrong number of direct hits calculated.");

  ndir = Ndir(track,geometry,hitsmap,-15.,75.);
  ENSURE_DISTANCE(ndir,4.,0.0001,
		  "Wrong number of direct hits calculated.");

  ndir = Ndir(track,geometry,hitsmap,-15.,150.);
  ENSURE_DISTANCE(ndir,5.,0.0001,
		  "Wrong number of direct hits calculated.");
}

TEST(AllCuts_TiltedTrack)
{
  double ang = theta_cherenkov; // Cherenkov angle

  I3Particle track(I3Particle::InfiniteTrack);
  track.SetPos(10,10,0);
  track.SetDir(180*deg-ang,90*deg);
  track.SetTime(15);

  vector<I3Position> pos;
  I3Position p(10,10,20);  pos.push_back(p);
  p.SetPos(10,0,100);  pos.push_back(p);
  p.SetPos(10,50,0);  pos.push_back(p);

  vector<double> time;
  double t = 20/c_ice + 15 + 17;  time.push_back(t);
  t = (10/sin(ang) + (100-10/tan(ang)))/c_ice + 15 - 9;  time.push_back(t);
  t = 40*(1/(c_ice*tan(ang)) - 1/(c*sin(ang))) + 15 + 3;  time.push_back(t);

  string hitseries = "NdirTest";
  I3Geometry geometry = CalcGeom(pos);
  I3RecoHitSeriesMap hitsmap = CalcHits(time);

  double ndir = Ndir(track,geometry,hitsmap,-15.,25.);
  ENSURE_DISTANCE(ndir,3.,0.0001,
		  "Wrong number of direct hits calculated.");

  double ldir = Ldir(track,geometry,hitsmap,-15.,15.);
  ENSURE_DISTANCE(ldir,108.40697,0.001,
		  "Wrong Ldir distance calculated.");

  double smooth = SmoothAll(track,geometry,hitsmap);
  ENSURE_DISTANCE(smooth,0.119454,0.0001,
		 "Wrong smoothness calculated.");

  double smoothdir = SmoothDir(track,geometry,hitsmap);
  ENSURE_DISTANCE(smoothdir,0.119454,0.0001,
		 "Wrong smoothnessDir calculated.");
}
