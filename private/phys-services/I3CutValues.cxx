/**
  This class has been deprecated!
  The name has been changed to I3TrackCutValues to differentiate
  between I3CascadeCutValues
*/

#include "icetray/serialization.h"
#include "phys-services/I3Cuts.h"
#include "phys-services/I3CutValues.h"

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
