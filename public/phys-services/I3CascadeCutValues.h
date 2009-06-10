/**
    copyright  (C) 2005
    the icecube collaboration
    $Id: I3CascadeCutValues.h 10512 2008-03-16 15:02:51 mdagost $
    @author mdagost
*/

#ifndef I3CASCADECUTVALUES_H
#define I3CASCADECUTVALUES_H

#include "icetray/I3FrameObject.h"
#include "dataclasses/Utility.h"
#include "dataclasses/I3Units.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "phys-services/I3Cuts.h"

/**
 * @brief A class to store the basic hit information for cascades from the event
 */
class I3CascadeCutValues : public I3FrameObject
{
 public:
  int Nchan;
  int Nhit;
  int N_1hit;
  int Nstring;
  int Ndir;
  int Nearly;
  int Nlate;
  I3Position cog;

  I3CascadeCutValues() :
    Nchan(-1),
    Nhit(-1),
    N_1hit(-1),
    Nstring(-1),
    Ndir(-1),
    Nearly(-1),
    Nlate(-1)
    { cog.NullPos(); };

  void Calculate(const I3Particle& vertex, 
		 const I3Geometry& geometry, 
		 const I3RecoHitSeriesMap& hitmap,
		 const double& begTWindow = I3Constants::dt_window_l,
		 const double& endTWindow = I3Constants::dt_window_h);

  void Calculate(const I3Particle& vertex, 
		 const I3Geometry& geometry, 
		 const I3RecoPulseSeriesMap& pulsemap,
		 const double& begTWindow = I3Constants::dt_window_l,
		 const double& endTWindow = I3Constants::dt_window_h);

  virtual ~I3CascadeCutValues();

 private:

  friend class boost::serialization::access;
  template <class Archive> void serialize(Archive & ar, unsigned version);

};

I3_POINTER_TYPEDEFS(I3CascadeCutValues);

#endif
