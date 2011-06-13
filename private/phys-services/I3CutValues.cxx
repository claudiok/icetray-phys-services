#include "icetray/serialization.h"
#include "icetray/I3FrameObject.h"
#include "phys-services/I3Cuts.h"
#include "phys-services/I3CutValues.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/geometry/I3Geometry.h"

void I3CutValues::Calculate(const I3Particle& track, 
			    const I3Geometry& geometry, 
			    const I3RecoPulseSeriesMap& pulsemap,
			    const double& begTWindow,
			    const double& endTWindow)
{
  I3Cuts::CutsCalc(track, geometry, pulsemap, begTWindow, endTWindow,
		   Nchan, Nhit, Nstring, Ndir, Ldir, Sdir, Sall);
  cog = I3Cuts::COG(geometry, pulsemap);
}

I3CutValues::~I3CutValues() { }

template <class Archive>
void I3CutValues::serialize(Archive& ar, unsigned version)
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
  
BOOST_CLASS_VERSION(I3CutValues, 1);
I3_SERIALIZABLE(I3CutValues);
