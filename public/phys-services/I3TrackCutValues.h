/**
    copyright  (C) 2005
    the icecube collaboration
    $Id: I3CutValues.h 10512 2005-08-03 19:04:51Z dule $
    @author dule
*/

#ifndef I3TRACKCUTVALUES_H
#define I3TRACKCUTVALUES_H

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
class I3TrackCutValues : public I3FrameObject
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

  I3TrackCutValues() :
    Nchan(-1),
    Nhit(-1),
    Nstring(-1),
    Ndir(-1),
    Ldir(NAN),
    Sdir(NAN),
    Sall(NAN)
    { cog.NullPos(); };

  void Calculate(const I3Particle& track, 
		 const I3Geometry& geometry, 
		 const I3RecoHitSeriesMap& hitmap,
		 const double& begTWindow = I3Constants::dt_window_l,
		 const double& endTWindow = I3Constants::dt_window_h);

  void Calculate(const I3Particle& track, 
		 const I3Geometry& geometry, 
		 const I3RecoPulseSeriesMap& pulsemap,
		 const double& begTWindow = I3Constants::dt_window_l,
		 const double& endTWindow = I3Constants::dt_window_h);

  virtual ~I3TrackCutValues();

 private:

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive & ar, unsigned version);

};

I3_POINTER_TYPEDEFS(I3TrackCutValues);

#endif