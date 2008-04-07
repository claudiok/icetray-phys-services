/**
 * $Id: I3CutsStd.h$
 * (c) 2008 IceCube Collaboration
 * @author J.Dumm, plagiarizing from D.Turcan
 */

#ifndef I3CUTSSTD_H
#define I3CUTSSTD_H

#include "dataclasses/I3Units.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/geometry/I3Geometry.h"
#include "phys-services/I3Cuts.h"

/**
 * @brief The I3CutsStd namespace is a collection of functions that calculate 
 * various cut parameters for reconstruction.  These include things like 
 * Ndir, Ldir, Smoothness in several standard time windows,
 * and now ContainmentSize (cSize), and Length of all hits (Lall).
 * The standard windows are: A [-15,15]ns
 *                           B [-15,25]ns
 *                           C [-15,75]ns
 *                           D [-15,150]ns
 *                           E [-15,250]ns
 * 
 * @todo So far we have Ndir, Ldir, and Smoothness, but other cut parameters
 * will and should be added as we have move more into an analysis phase of the 
 * experiment.
 */
namespace I3CutsStd
{
  /**
   * Main function that does the actual calculation of all of the cut 
   * parameters.  First, it loops over all hits 
   * (or pulses), makes "projections" of the hits onto the input track, and 
   * calculates the time residual for each hit (difference between the 
   * expected and actual time of arrival of the Cherenkov photon from the 
   * given track and the OM).  If the time residual is within some set time 
   * window, then the hit is tagged as "direct hit".  Then, based on the 
   * times and distances of the direct (or all) hits, it calculates the 3 
   * quantities, according to their individual algorithms.
   * 
   * 
   * INPUT:
   * @param track --  Track used in calculation.
   * @param geometry -- Geometry object from the event.
   * @param hitmap -- Map of I3RecoHitSeries used in calculation. 
   * @param t1 -- Lower edge of the time residual window for direct hits.
   *              Generally, this value is -15ns.
   * @param t2 -- Upper edge of the time residual window for direct hits.
   *              Generally, this value is 15ns..150ns.
   * 
   * 
   * OUTPUT:
   * @param Nchan -- The Nchan cut parameter: total number of hit channels.
   * @param Nhit -- The Nhit cut parameter: total number of hits.
   * @param Nstring -- The Nstring cut parameter: total number of strings.
   * @param Nearly  -- The Nearly cut parameter: total number of hits with time
                       residuals < -15 ns.
   * @param Nlate  -- The Nlate cut parameter: total number of hits with time
                       residuals > 250 ns.
   * @param Ndir -- The Ndir cut parameter: number of direct hits.
   * @param Ldir -- The Ldir cut parameter (based on direct hits): "length" 
   *                of the event.  This is the length between the two most 
   *                extreme projections of the direct hits onto the track.  
   * @param Sall -- The Smoothness parameter (based on all hits): how 
   *                uniformly are the hit projections onto the track 
   *                distributed along that track.
   * @param Sdir -- The Smoothness parameter (based on direct hits): how 
   *                uniformly are the hit projections onto the track 
   *                distributed along that track.
   * 
   * 
   * @todo Think about making the code more efficient...
   */
  void TrackCutsCalc(const I3Particle& track, 
		const I3Geometry& geometry, 
		const I3RecoHitSeriesMap& hitmap,
		int& Nchan, 
 		int& Nhit,
		int& Nstring,
		int& Nearly,
		int& Nlate,
		int& NdirA, 
		double& LdirA,
		double& SdirA,
		int& NdirB, 
		double& LdirB,
		double& SdirB,
		int& NdirC, 
		double& LdirC,
		double& SdirC,
		int& NdirD, 
		double& LdirD,
		double& SdirD,
		int& NdirE, 
		double& LdirE,
		double& SdirE,
		double& Sall,
        double& Lall);

  /**
   * INPUT:
   * @parameter pulsemap -- Map of I3RecoPulseSeries to be used.
   */
  void TrackCutsCalc(const I3Particle& track, 
		const I3Geometry& geometry, 
		const I3RecoPulseSeriesMap& pulsemap,
		int& Nchan, 
		int& Nhit, 
		int& Nstring,
		int& Nearly,
		int& Nlate,
		int& NdirA, 
		double& LdirA,
		double& SdirA,
		int& NdirB, 
		double& LdirB,
		double& SdirB,
		int& NdirC, 
		double& LdirC,
		double& SdirC,
		int& NdirD, 
		double& LdirD,
		double& SdirD,
		int& NdirE, 
		double& LdirE,
		double& SdirE,
		double& Sall,
        double& Lall);


  /**
   * Main function that does the actual calculation of all of the cut 
   * parameters.  First, it loops over all hits 
   * 
   * INPUT:
   * @param vertex --  Vertex used in calculation.
   * @param geometry -- Geometry object from the event.
   * @param hitmap -- Map of I3RecoHitSeries used in calculation. 
   * @param t1 -- Lower edge of the time residual window for direct hits.
   *              Generally, this value is -15ns.
   * @param t2 -- Upper edge of the time residual window for direct hits.
   *              Generally, this value is 15ns..150ns.
   * 
   * 
   * OUTPUT:
   * @param Nchan -- The Nchan cut parameter: total number of hit channels.
   * @param Nhit -- The Nhit cut parameter: total number of hits.
   * @param N_1hit -- Number of channels with only 1 hit in them.
   * @param Nstring -- The Nstring cut parameter: total number of strings.
   * @param Ndir -- The Ndir cut parameter: number of direct hits.
   * @param Nearly -- The Nearly cut parameter: number of early hits.
   * @param Nlate -- The Nlate cut parameter: number of late hits.
   * 
   * @todo Think about making the code more efficient...
   */
  void CascadeCutsCalc(const I3Particle& vertex, 
                       const I3Geometry& geometry, 
                       const I3RecoHitSeriesMap& hitmap,
                       int& Nchan, 
                       int& Nhit,
                       int& N_1hit,
                       int& Nstring,
                       int& NdirA, 
                       int& NearlyA,
                       int& NlateA,
                       int& NdirB, 
                       int& NearlyB,
                       int& NlateB,
                       int& NdirC, 
                       int& NearlyC,
                       int& NlateC,
                       int& NdirD, 
                       int& NearlyD,
                       int& NlateD, 
		       int& NdirE, 
                       int& NearlyE,
                       int& NlateE);

  /**
   * INPUT:
   * @parameter pulsemap -- Map of I3RecoPulseSeries to be used.
   */
  void CascadeCutsCalc(const I3Particle& vertex, 
                       const I3Geometry& geometry, 
                       const I3RecoPulseSeriesMap& pulsemap,
                       int& Nchan, 
                       int& Nhit, 
                       int& N_1hit, 
                       int& Nstring,
                       int& NdirA, 
                       int& NearlyA,
                       int& NlateA,
                       int& NdirB, 
                       int& NearlyB,
                       int& NlateB,
                       int& NdirC, 
                       int& NearlyC,
                       int& NlateC,
                       int& NdirD, 
                       int& NearlyD,
                       int& NlateD, 
		       int& NdirE, 
                       int& NearlyE,
                       int& NlateE);


  /**
   * A function which calculates the center of gravity of the hits. 
   * It takes a I3RecoPulseSeries map and the geometry,
   * and returns an I3Position of the COG.
   */
  I3Position COG(const I3Geometry& geometry,
		 const I3RecoPulseSeriesMap& pulsemap);

  /**
   * Use I3RecoHitSeries instead of I3RecoPulseSeries.
   */
  I3Position COG(const I3Geometry& geometry,
		 const I3RecoHitSeriesMap& hitmap);

  // JD: I deleted a lot of convenience functions here.  Can be added back later.

  // Added Kath's calc of ContainmentVolumeSize, cSize 
  double InIceContainmentSize(I3Geometry geo, I3Particle p);


}

#endif

