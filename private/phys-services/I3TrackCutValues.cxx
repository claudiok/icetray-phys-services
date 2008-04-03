#include "icetray/serialization.h"
#include "phys-services/I3Cuts.h"
#include "phys-services/I3TrackCutValues.h"

void I3TrackCutValues::Calculate(const I3Particle& track, 
			    const I3Geometry& geometry, 
			    const I3RecoHitSeriesMap& hitmap,
			    const double& begTWindow,
			    const double& endTWindow)
{
  I3Cuts::TrackCutsCalc(track, geometry, hitmap, begTWindow, endTWindow,
		   Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  cog = I3Cuts::COG(geometry, hitmap);
}

void I3TrackCutValues::Calculate(const I3Particle& track, 
			    const I3Geometry& geometry, 
			    const I3RecoPulseSeriesMap& pulsemap,
			    const double& begTWindow,
			    const double& endTWindow)
{
  I3Cuts::TrackCutsCalc(track, geometry, pulsemap, begTWindow, endTWindow,
		   Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  cog = I3Cuts::COG(geometry, pulsemap);
}

I3TrackCutValues::~I3TrackCutValues() { }

template <class Archive>
void I3TrackCutValues::serialize(Archive& ar, unsigned version)
{
  ar & make_nvp("I3FrameObject", base_object<I3FrameObject>(*this));
  ar & make_nvp("Nchan",Nchan);
  ar & make_nvp("Nhit",Nhit);
  if (version > 0) 
    ar & make_nvp("Nstring",Nstring);
  ar & make_nvp("Ndir",Ndir);
  ar & make_nvp("Ldir",Ldir);
  ar & make_nvp("Sdir",Sdir);
  if (version > 0) 
    ar & make_nvp("Sall",Sall);
  ar & make_nvp("cog",cog);
}
  
BOOST_CLASS_VERSION(I3TrackCutValues, 1);
I3_SERIALIZABLE(I3TrackCutValues);
