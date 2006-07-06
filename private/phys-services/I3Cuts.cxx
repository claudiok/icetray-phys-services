//#include <vector>
#include "phys-services/I3Cuts.h"
#include "dataclasses/I3Constants.h"
#include "phys-services/Utility.h"
#include "phys-services/I3Calculator.h"
#include <cassert>

using namespace I3Constants;
using namespace I3Calculator;


//--------------------------------------------------------------
template<class HitType>
void CutsCalcImpl(const I3Particle& track, const I3Geometry& geometry, 
		  const I3Map<OMKey, vector<HitType> >& hitmap,
		  const double t1, const double t2,int& Nchan, int& Nhit, int& Nstring,
		  int& Ndir, double& Ldir, double& Sdir, double& Sall)
{
  int StringNumber[120] = {0};
  Ndir = 0;
  Nhit = 0;
  Nstring = 0;
  vector<double> lengthAll;
  vector<double> lengthDir;
  double min = 999999;
  double max = -999999;
  typename I3Map<OMKey, vector<HitType> >::const_iterator hits_i;
  for (hits_i=hitmap.begin(); hits_i!=hitmap.end(); hits_i++) {
    const vector<HitType>& hits = hits_i->second;
    OMKey omkey = hits_i->first;
    I3OMGeoMap::const_iterator geom = geometry.omgeo.find(omkey);
    if (geom==geometry.omgeo.end()) {
      log_debug("Didn't find the current OMKey in Geometry");
      continue;
    }

    StringNumber[(int) 19+omkey.GetString()] = 1; // "19+" includes AMANDA strings
    const I3Position& ompos = geom->second.position;

    typename vector<HitType>::const_iterator hit;
    for (hit=hits.begin(); hit!=hits.end(); hit++) {
      
      double Tres = TimeResidual(track, ompos, hit->GetTime());
      log_trace("residual: %f",Tres);

      // calculate projections of hits onto track...
      Nhit++; // keep track of total hits
      I3Position pos(ompos);
      pos.ShiftCoordSystem(track.GetPos());
      pos.RotateZ(-track.GetDir().CalcPhi());
      pos.RotateY(-track.GetDir().CalcTheta());
      double dist = pos.GetZ();
      log_trace("dist: %f",dist);
      lengthAll.push_back(dist);        // set up for SmoothnessAll calculation

      // this is a direct hit...
      if (Tres>t1 && Tres<t2) {
	Ndir+=1;                     // add direct hits
	if (dist<min) min = dist;    // set minimum for "event length"
	if (dist>max) max = dist;    // set maximum for "event length"
	lengthDir.push_back(dist);  // set up for SmoothnessDir calculation
      }

    } // end loop over hitseries

  } // end loop over hitseriesmap

  //calculate Nstring
  for (int i = 0; i < 120; i++) {
    if (StringNumber[i])
      ++Nstring;
  }

    // calculate SmoothnessAll...
  {
    sort(lengthAll.begin(),lengthAll.end());
    for (unsigned int i=0; i<lengthAll.size(); i++) 
      log_trace("lengthAll[%i]=%f",i,lengthAll[i]);
    int N = lengthAll.size()-1;
    Sall = 0;
    for (unsigned int j=1; j<lengthAll.size(); j++) {
      double lj = lengthAll[j]-lengthAll[0];
      double lN = lengthAll[N]-lengthAll[0];
      double S = (double)j/(double)N - lj/lN;
      log_trace("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(Sall)) Sall = S;
    }
    // calculation is meaningless for less than 3 hits
    if(lengthAll.size() <= 2) Sall = NAN;
  }

  // calculate SmoothnessDir...
  {
    sort(lengthDir.begin(),lengthDir.end());
    for (unsigned int i=0; i<lengthDir.size(); i++) 
      log_trace("lengthDir[%i]=%f",i,lengthDir[i]);
    int N = lengthDir.size()-1;
    Sdir = 0;
    for (unsigned int j=1; j<lengthDir.size(); j++) {
      double lj = lengthDir[j]-lengthDir[0];
      double lN = lengthDir[N]-lengthDir[0];
      double S = (double)j/(double)N - lj/lN;
      log_trace("j: %i  N: %i  S: %f",j,N,S);
      if (fabs(S)>fabs(Sdir)) Sdir = S;
    }
    // calculation is meaningless for less than 3 direct hits
    if(lengthDir.size() <= 2) Sdir = NAN;
  }

  Ldir = max-min; // length of event
  if (lengthDir.size()==0) Ldir = NAN;
  Nchan = hitmap.size();
  log_debug("-----> Nchan: %i",Nchan);
  log_debug("-----> Ndir: %i",Ndir);
  log_debug("-----> Nhit: %i",Nhit);
  log_debug("-----> Nstring: %i",Nstring);
  log_debug("-----> Ldir: %f",Ldir);
  log_debug("-----> Sall: %f",Sall);
  log_debug("-----> Sdir: %f",Sdir);
  return;
}


//--------------------------------------------------------------
template<class HitType>
I3Position COGImpl(const I3Geometry& geometry,
		   const I3Map<OMKey, vector<HitType> >& hitmap)
{
  double ampWeight=1;
  const I3OMGeoMap& om_geo=geometry.omgeo;
  double cog[3];
  cog[0]=0.0;
  cog[1]=0.0;
  cog[2]=0.0;
  double ampsum=0.0;
  
  // I need to loop over all hit OMs, first to calculate the center of 
  // gravity of the hits and then to get the tensor of inertia.  
 
  typename I3Map<OMKey, vector<HitType> >::const_iterator iter;
  iter = hitmap.begin();
  while(iter != hitmap.end()) {
    
    const vector<HitType>& pulsevect = iter->second;

    if(pulsevect.empty()) {
      iter++;
      log_debug("empty RecoHitSeries or RecoPulseSeries!");
      continue;
    }
    
    for (unsigned i=0; i < pulsevect.size(); i++) {
      HitType pulse = pulsevect[i];
      double amp_tmp;
      if(isnan(GetCharge(pulse)) > 0 ) {
	amp_tmp=0;
      }
      else {
	amp_tmp = GetCharge(pulse);
      }

      double amp = pow(amp_tmp,ampWeight);
      ampsum+=amp;
    
      const OMKey om = iter->first;
      I3OMGeoMap::const_iterator iter2 = om_geo.find(om);
      assert(iter2 != om_geo.end());
      const I3Position& ompos = (iter2->second).position;
    
      // calculate the center of gravity             
      cog[0] += amp*ompos.GetX();
      cog[1] += amp*ompos.GetY();
      cog[2] += amp*ompos.GetZ();
    }
    iter++;
  }
  
  if (ampsum==0) ampsum=1.0;
  I3Position cogPosition(cog[0]/ampsum, cog[1]/ampsum, cog[2]/ampsum);
  return cogPosition;
}


//--------------------------------------------------------------
I3Position I3Cuts::COG(const I3Geometry& geometry,
		       const I3RecoHitSeriesMap& hitmap)
{
  I3Position cog(COGImpl<I3RecoHit>(geometry, hitmap));
  return cog;
}


//--------------------------------------------------------------
I3Position I3Cuts::COG(const I3Geometry& geometry,
		       const I3RecoPulseSeriesMap& pulsemap)
{
  I3Position cog(COGImpl<I3RecoPulse>(geometry, pulsemap));
  return cog;
}


//--------------------------------------------------------------
void I3Cuts::CutsCalc(const I3Particle& track, const I3Geometry& geometry, 
		      const I3RecoHitSeriesMap& hitmap,
		      const double t1, const double t2,int& Nchan, int& Nhit, int& Nstring,
		      int& Ndir, double& Ldir, double& Sdir, double& Sall)
{
  CutsCalcImpl<I3RecoHit>
    (track, geometry, hitmap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
}


//--------------------------------------------------------------
void I3Cuts::CutsCalc(const I3Particle& track, const I3Geometry& geometry, 
		      const I3RecoPulseSeriesMap& pulsemap,
		      const double t1, const double t2,int& Nchan, int& Nhit, int& Nstring,
		      int& Ndir, double& Ldir, double& Sdir, double& Sall)
{
  CutsCalcImpl<I3RecoPulse>
    (track, geometry, pulsemap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
}


//--------------------------------------------------------------
int I3Cuts::Nchan(const I3Particle& track, const I3Geometry& geom, 
		  const I3RecoHitSeriesMap& hitmap,
		  double t1, double t2)
{
  int Nchan, Nhit, Nstring, Ndir;
  double Ldir, Sdir, Sall;
  CutsCalcImpl<I3RecoHit>
    (track, geom, hitmap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  return Nchan;
}



//--------------------------------------------------------------
int I3Cuts::Nhit(const I3Particle& track, const I3Geometry& geom, 
		 const I3RecoHitSeriesMap& hitmap,
		 double t1, double t2)
{
  int Nchan, Nhit, Nstring, Ndir;
  double Ldir, Sdir, Sall;
  CutsCalcImpl<I3RecoHit>
    (track, geom, hitmap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  return Nhit;
}

//--------------------------------------------------------------
int I3Cuts::Nstring(const I3Particle& track, const I3Geometry& geom, 
		 const I3RecoHitSeriesMap& hitmap,
		 double t1, double t2)
{
  int Nchan, Nhit, Nstring, Ndir;
  double Ldir, Sdir, Sall;
  CutsCalcImpl<I3RecoHit>
    (track, geom, hitmap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  return Nstring;
}

//--------------------------------------------------------------
int I3Cuts::Ndir(const I3Particle& track, const I3Geometry& geom, 
		 const I3RecoHitSeriesMap& hitmap,
		 double t1, double t2)
{
  int Nchan, Nhit, Nstring, Ndir;
  double Ldir, Sdir, Sall;
  CutsCalcImpl<I3RecoHit>
    (track, geom, hitmap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  return Ndir;
}


//--------------------------------------------------------------
double I3Cuts::Ldir(const I3Particle& track, const I3Geometry& geom, 
		    const I3RecoHitSeriesMap& hitmap,
		    double t1, double t2)
{
  int Nchan, Nhit, Nstring, Ndir;
  double Ldir, Sdir, Sall;
  CutsCalcImpl<I3RecoHit>
    (track, geom, hitmap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  return Ldir;
}


//--------------------------------------------------------------
double I3Cuts::SmoothAll(const I3Particle& track, const I3Geometry& geom, 
			 const I3RecoHitSeriesMap& hitmap,
			 double t1, double t2)
{
  int Nchan, Nhit, Nstring, Ndir;
  double Ldir, Sdir, Sall;
  CutsCalcImpl<I3RecoHit>
    (track, geom, hitmap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  return Sall;
}


//--------------------------------------------------------------
double I3Cuts::SmoothDir(const I3Particle& track, const I3Geometry& geom, 
			 const I3RecoHitSeriesMap& hitmap,
			 double t1, double t2)
{
  int Nchan, Nhit, Nstring, Ndir;
  double Ldir, Sdir, Sall;
  CutsCalcImpl<I3RecoHit>
    (track, geom, hitmap, t1, t2, Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  return Sdir;
}

//--------------------------------------------------------------
// Computes the size of the "cylinder of closest approach", as defined
// in Kath's thesis appendix A
double I3Cuts::CylinderSize(const I3Particle& track, 
			    //I3Geometry& geom, 
			    //I3OMResponseMap& ommap, 
			    double H0, double R0, double center) {

  I3Direction v = track.GetDir();
  I3Position p = track.GetPos();

  // X, Y, and Z
  double xx = p.GetX();
  double yy = p.GetY();
  double zz = p.GetZ();

  // Theta and Phi must be in RADIANS
  //double px = -cos(phi)*sin(theta);
  //double py = -sin(phi)*sin(theta);
  //double pz = -cos(theta);
  double px = v.GetX();
  double py = v.GetY();
  double pz = v.GetZ();

  double k, r;
  double aa, bb, cc, underroot, root1, root2, z1, z2;
  double bestcorner, bestcyl, zcyl, zprime;

  // Typical values for AMANDA-B10:
  // H0 = 175,
  // R0 = 100,
  // center = 45

  k = R0/H0;

  //###########################################
  // smallest cylindrical volume of radius r and total height h around 
  // (0,0,center), which is proportional to R0, H0 and contains the track 

  // 1) Solve for top/bottom clippers

  zprime = zz - center;

  aa = px*px+py*py-k*k*pz*pz;
  bb = 2*(xx*px + yy*py -k*k*zprime*pz);
  cc = xx*xx + yy*yy-k*k*zprime*zprime;
  underroot = bb*bb - 4*aa*cc;

  if (underroot >= 0.) {
    root1 = 0.5*(-bb + sqrt(underroot))/aa;
    root2 = 0.5*(-bb - sqrt(underroot))/aa;
    z1 = fabs(zprime + root1*pz);
    z2 = fabs(zprime + root2*pz);

    if (z2<z1) {
      bestcorner = z2/H0;
    } else {
      bestcorner = z1/H0;
    }

  } else {
    bestcorner = NAN;
  }

  // 2) Solve for cylinder-clipper
  if ((px==0) && (py==0)) {
    //  it's straight vertical
    r = xx*xx + yy*yy;
    if (r > 0) {
      r = sqrt(r);
    } else {
      r = 0.;
    }
    bestcyl = r/R0;
  } else {
    // not straight vertical
    r = (xx*xx + yy*yy -
         ((px*xx + py*yy)*(px*xx + py*yy))/(px*px + py*py));
    if (r > 0) {
      r = sqrt(r);
    } else {
      r = 0.;
    }

    // But wait!  It must have at least the proper r/h ratio
    zcyl = fabs(zprime + (-(px*xx+py*yy)/(px*px+py*py))*pz);
    if (r/zcyl >= k) {
      bestcyl = r/R0;
    } else {
      bestcyl = NAN;
    }
  }

  // Which is smaller?
  if ((bestcorner<bestcyl)||isnan(bestcyl)) {
    return bestcorner;
  } else {
    return bestcyl;
  }

}


