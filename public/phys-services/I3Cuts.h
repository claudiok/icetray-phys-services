#ifndef I3CUTS_H
#define I3CUTS_H

#include "dataclasses/I3Units.h"
#include "dataclasses/physics/I3Particle.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/geometry/I3Geometry.h"


/**
 * @brief The I3Cuts namespace is a collection of functions that calculate 
 * various cut parameters for reconstruction.  These include things like 
 * Ndir, Ldir, and Smoothness.
 * 
 * @todo So far we have Ndir, Ldir, and Smoothness, but other cut parameters
 * will and should be added as we have move more into an analysis phase of the 
 * experiment.
 */
namespace I3Cuts
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
  void CutsCalc(const I3Particle& track, 
		const I3Geometry& geometry, 
		const I3RecoHitSeriesMap& hitmap,
		const double t1, 
		const double t2, 
		int& Nchan, 
 		int& Nhit,
		int& Nstring,
		int& Ndir, 
		double& Ldir,
		double& Sdir,
		double& Sall);

  /**
   * INPUT:
   * @parameter pulsemap -- Map of I3RecoPulseSeries to be used.
   */
  void CutsCalc(const I3Particle& track, 
		const I3Geometry& geometry, 
		const I3RecoPulseSeriesMap& pulsemap,
		const double t1, 
		const double t2, 
		int& Nchan, 
		int& Nhit, 
		int& Nstring,
		int& Ndir, 
		double& Ldir,
		double& Sdir,
		double& Sall);

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

  /**
   * A convenience function that calls CutsCalc() and returns the total 
   * number of channels (hit OMs) in the event.  If you are interested in
   * more than one quantity from CutsCalc(), use the CutsCalc() function 
   * directly, in order to save multiple calls to the function.
   */
  int Nchan(const I3Particle& track, 
	   const I3Geometry& geom, 
	   const I3RecoHitSeriesMap& hitmap, 
	   double t1 = I3Constants::dt_window_l, 
	   double t2 = I3Constants::dt_window_h);

  /**
   * A convenience function that calls CutsCalc() and returns the total 
   * number of hits in the event.  If you are interested in more than 
   * one quantity from CutsCalc(), use the CutsCalc() function directly,
   * in order to save multiple calls to the function.
   */
  int Nhit(const I3Particle& track, 
	   const I3Geometry& geom, 
	   const I3RecoHitSeriesMap& hitmap, 
	   double t1 = I3Constants::dt_window_l, 
	   double t2 = I3Constants::dt_window_h);

  /**
   * A convenience function that calls CutsCalc() and returns the total 
   * number of strings in the event.  If you are interested in more than 
   * one quantity from CutsCalc(), use the CutsCalc() function directly,
   * in order to save multiple calls to the function.
   */
  int Nstring(const I3Particle& track, 
	   const I3Geometry& geom, 
	   const I3RecoHitSeriesMap& hitmap, 
	   double t1 = I3Constants::dt_window_l, 
	   double t2 = I3Constants::dt_window_h);

  /**
   * A convenience function that calls CutsCalc() and returns the number 
   * of direct hits from a given track.  If you are interested in more than 
   * one quantity from CutsCalc(), use the CutsCalc() function directly,
   * in order to save multiple calls to the function.
   */
  int Ndir(const I3Particle& track, 
	   const I3Geometry& geom, 
	   const I3RecoHitSeriesMap& hitmap, 
	   double t1 = I3Constants::dt_window_l, 
	   double t2 = I3Constants::dt_window_h);

  /**
   * A convenience function that calls CutsCalc() and returns the 
   * "direct-hits length" of the event.  If you are interested in more than  
   * one quantity from CutsCalc(), use the CutsCalc() function directly, 
   * in order to save multiple calls to the function.
   */
  double Ldir(const I3Particle& track, 
	      const I3Geometry& geom, 
	      const I3RecoHitSeriesMap& hitmap, 
	      double t1 = I3Constants::dt_window_l, 
	      double t2 = I3Constants::dt_window_h);

  /**
   * A convenience function that calls CutsCalc() and returns the 
   * "direct-hits smoothness" of the event.  If you are interested in more   
   * than one quantity from CutsCalc(), use the CutsCalc() function, 
   * directly in order to save multiple calls to the function.
   */
  double SmoothDir(const I3Particle& track, 
		   const I3Geometry& geom, 
		   const I3RecoHitSeriesMap& hitmap, 
		   double t1 = I3Constants::dt_window_l, 
		   double t2 = I3Constants::dt_window_h);

  /**
   * A convenience function that calls CutsCalc() and returns the 
   * "all-hits smoothness" of the event.  If you are interested in more than  
   * one quantity from CutsCalc(), use the CutsCalc() function directly, 
   * in order to save multiple calls to the function.
   */
  double SmoothAll(const I3Particle& track, 
		   const I3Geometry& geom, 
		   const I3RecoHitSeriesMap& hitmap, 
		   double t1 = I3Constants::dt_window_l, 
		   double t2 = I3Constants::dt_window_h);

  /**
   * Computes the size of the "cylinder of closest approach", 
   * which is the amount by which one must expand a "reference cylinder"
   * (such as the volume of the in-ice detector) in order to just barely
   * contain the track.
   * For grusome defail, see Kath's thesis appendix A.
   *
   * "H0" = height of reference cylinder
   * "R0" = radius of reference cylinder
   * "center" = z-coordinate of center of reference cylinder
   *           (the x- and y-coordinates are assumed to be at zero)
   *
   * This is useful, for instance, for making cuts on whether a track goes
   * through the physical volume of the in-ice detector, close to the center,
   * or outside of it.
   */
  double CylinderSize(const I3Particle& track, 
		      double H0, 
		      double R0, 
		      double center);


}

#endif

