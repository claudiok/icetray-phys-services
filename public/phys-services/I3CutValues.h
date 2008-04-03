/**
    copyright  (C) 2005
    the icecube collaboration
    $Id: I3CutValues.h 10512 2005-08-03 19:04:51Z dule $
    @author dule
    @brief This class has been deprecated and will be removed!
           The name changed to I3TrackCutValues to differentiate 
           between I3CascadeCutValues
*/

#ifndef I3CUTVALUES_H
#define I3CUTVALUES_H

#include "icetray/I3FrameObject.h"
#include "dataclasses/Utility.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "phys-services/I3Cuts.h"

/**
 * @brief A class to store the basic hit information from the event
 */
class I3CutValues : public I3FrameObject
{
 public:
  int Nchan;
  int Nhit;
  int Nstring;
  int Ndir;
  double Ldir;
  double Sdir;
  double Sall;
  I3Position cog;

 private:

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive & ar, unsigned version);

};

I3_POINTER_TYPEDEFS(I3CutValues);

#endif
