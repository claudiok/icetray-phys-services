#include "dataclasses/BoostHeaders.h"
#include "phys-services/I3Cuts.h"
#include "phys-services/I3CutValues.h"

void I3CutValues::Calculate(const I3Particle& track, 
			    const I3Geometry& geometry, 
			    const I3RecoHitSeriesMap& hitmap,
			    const double& begTWindow,
			    const double& endTWindow)
{
  I3Cuts::CutsCalc(track, geometry, hitmap, begTWindow, endTWindow,
		   Nchan, Nhit, Ndir, Ldir, Sdir, Sall);
  cog = I3Cuts::COG(geometry, hitmap);
}

void I3CutValues::Calculate(const I3Particle& track, 
			    const I3Geometry& geometry, 
			    const I3RecoPulseSeriesMap& pulsemap,
			    const double& begTWindow,
			    const double& endTWindow)
{
  I3Cuts::CutsCalc(track, geometry, pulsemap, begTWindow, endTWindow,
		   Nchan, Nhit, Ndir, Ldir, Sdir, Sall);
  cog = I3Cuts::COG(geometry, pulsemap);
}

I3CutValues::~I3CutValues() { }

template <class Archive>
void I3CutValues::serialize(Archive& ar, unsigned version)
{
  ar & make_nvp("I3FrameObject", base_object<I3FrameObject>(*this));
  ar & make_nvp("Nchan",Nchan);
  ar & make_nvp("Nhit",Nhit);
  ar & make_nvp("Ndir",Ndir);
  ar & make_nvp("Ldir",Ldir);
  ar & make_nvp("Sdir",Sdir);
  ar & make_nvp("Sall",Sall);
  ar & make_nvp("cog",cog);
}
  

I3_SERIALIZABLE(I3CutValues);
