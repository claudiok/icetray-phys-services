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

TEST(CylinderSize)
{
  // AMANDA numbers
  double H0 = 175;
  double R0 = 100;
  double center = 45;
  //const I3Position detectorcenter(0,0,center);

  double cylsiz;
  I3Particle t(I3Particle::InfiniteTrack);

  // Check the "cylindersize" parameter
  // -----------------------------------
  // Corner-clipper:
  t.SetPos(100,100,2000);
  t.SetDir(0.005,0);
  cylsiz = CylinderSize(t, H0, R0, center);
  ENSURE_DISTANCE(cylsiz, 1.339, 0.0001, "CylinderSize corner-clipper not working");
  
  // Edge-grazer:
  t.SetPos(50,1000,1000);
  t.SetDir(45*deg,90*deg);
  cylsiz = CylinderSize(t, H0, R0, center);
  ENSURE_DISTANCE(cylsiz, 0.50, 0.0001, "CylinderSize edge-grazer not working");

}

TEST(CMPolygon)
{
  vector<double> x;
  vector<double> y;
  double xcm, ycm;

  // Simple case: rectangle
  x.push_back(0);
  x.push_back(4);
  x.push_back(4);
  x.push_back(0);
  y.push_back(0);
  y.push_back(0);
  y.push_back(2);
  y.push_back(2);
  CMPolygon(x,y,&xcm,&ycm);
  ENSURE_EQUAL(xcm,2,"Rectangle CM is wrong (x)");
  ENSURE_EQUAL(ycm,1,"Rectangle CM is wrong (y)");

  // Another simple case:
  // Circle, centered on a point other than zero
  double R = 200;
  double centerx = 36;
  double centery = 12;
  vector<double> xcir;
  vector<double> ycir;
  int npoints = 100;
  for (int i=0; i<npoints; i++) {
    double th = 360*deg/npoints*i;
    xcir.push_back(centerx + R*sin(th));
    ycir.push_back(centery + R*cos(th));
  }
  CMPolygon(xcir,ycir,&xcm,&ycm);
  ENSURE_DISTANCE(xcm,36,0.001, "Circle CM is wrong (x)");
  ENSURE_DISTANCE(ycm,12,0.001, "Circle CM is wrong (y)");
  
  // The IT-16 Rhombus
  x.clear();
  y.clear();
  x.push_back(437.33);
  x.push_back(171.48);
  x.push_back(365.71);
  x.push_back(600.45);
  y.push_back(-209.85);
  y.push_back(119.39);
  y.push_back(428.2);
  y.push_back(144.06);
  CMPolygon(x,y,&xcm,&ycm);
  ENSURE_DISTANCE(xcm,392.0216,0.0001, "IT-16 Rhombus CM is wrong (x)");
  ENSURE_DISTANCE(ycm,116.4436,0.0001, "IT-16 Rhombus CM is wrong (y)");
 
  // The IT-16 Rhombus with its points out of order
  // Should be the same answer as above!
  x.clear();
  y.clear();
  x.push_back(437.33);
  x.push_back(365.71);
  x.push_back(171.48);
  x.push_back(600.45);
  y.push_back(-209.85);
  y.push_back(428.2);
  y.push_back(119.39);
  y.push_back(144.06);
  CMPolygon(x,y,&xcm,&ycm);
  ENSURE_DISTANCE(xcm,392.0216,0.0001, "IT-16 out-of-order Rhombus CM is wrong (x)");
  ENSURE_DISTANCE(ycm,116.4436,0.0001, "IT-16 out-of-order Rhombus CM is wrong (y)");
 

}


TEST(Containment_Rectangle)
{

  // Olga's first test-case... a rectangle like this:
  //   (0,2)             (4,2)
  //     x   x   x   x   x
  //     x   x   x   x   x
  //     x   x   x   x   x
  //   (0,0)             (4,2)
  // One-dimensional case
  vector<double> x;  // = (0,4,4,0);
  x.push_back(0);
  x.push_back(4);
  x.push_back(4);
  x.push_back(0);
  vector<double> y;  // = (0,0,2,2);
  y.push_back(0);
  y.push_back(0);
  y.push_back(2);
  y.push_back(2);
  double z=0;
  I3Particle seed;
  seed.SetShape(I3Particle::InfiniteTrack);
  seed.SetFitStatus(I3Particle::OK);
  double c;

  // The "point" is at (1.0,1.5)
  // Actually, just a little bit off so it doesn't land exactly...
  seed.SetPos(1.01, 1.5, 0);
  seed.SetDir(0, 0);
  c = ContainmentAreaSize(seed, x, y, z);
  ENSURE_DISTANCE(c, 0.5, 0.0001, "Square C didn't work");

  // The "point" is at (1.0,1.5)
  // This time make it land exactly (this is a special case)
  seed.SetPos(1.0, 1.5, 0);
  seed.SetDir(0, 0);
  c = ContainmentAreaSize(seed, x, y, z);
  ENSURE_DISTANCE(c, 0.5, 0.0001, "Square C didn't work");

}


TEST(Containment_IceTopRhombus)
{

  // This time, input the four "corners" of the rhombus of IceTop-16
  vector<double> x;  // = (0,4,4,0);
  x.push_back(437.33);
  x.push_back(171.48);
  x.push_back(365.71);
  x.push_back(600.45);
  vector<double> y;  // = (0,0,2,2);
  y.push_back(-209.85);
  y.push_back(119.39);
  y.push_back(428.2);
  y.push_back(144.06);
  double z=0;
  I3Particle seed;
  seed.SetShape(I3Particle::InfiniteTrack);
  seed.SetFitStatus(I3Particle::OK);
  double c;

  // The "point"
  seed.SetPos(300, 200, 0);
  seed.SetDir(0, 0);
  c = ContainmentAreaSize(seed, x, y, z);
  //ENSURE_DISTANCE(c, 0.64, 0.005, "Rhombus C didn't work");
  ENSURE_DISTANCE(c, 0.6501, 0.0001, "Rhombus C didn't work");

}
