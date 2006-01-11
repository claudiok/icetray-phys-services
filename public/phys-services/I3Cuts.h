#ifndef I3CUTS_H
#define I3CUTS_H

#include "dataclasses/I3Units.h"
#include "dataclasses/I3Track.h"
#include "dataclasses/I3OMResponseMap.h"
#include "dataclasses/I3Geometry.h"

using namespace I3Units;


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
   * The default value for the lower edge of the residual time window for
   * direct hits.
   */
  static const double minusTWindow = -15*ns;

  /**
   * The default value for the upper edge of the residual time window for
   * direct hits.
   */
  static const double plusTWindow  = +25*ns;

  /**
   * Main function that does the actual calculation of Ndir, Ldir, and 
   * Smoothness, based on direct hits.  First, it loops over all hits 
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
   * @param track -- Smart pointer to the track object.
   * @param geom -- The geometry object from the event.
   * @param ommap -- The OMResponseMap object from which to extract the 
   *                 OMResponse.
   * @param hitseries -- Name of the RecoHitSeries or RecoPulseSeries which 
   *                     contains the desired hit information.
   * @param t1 -- Lower edge of the time residual window for direct hits.
   *              Generally, this value is -15ns.
   * @param t2 -- Upper edge of the time residual window for direct hits.
   *              Generally, this value is 15ns..150ns.
   * 
   * 
   * OUTPUT:
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
  void DirectHits(const I3Track& track, 
		  I3Geometry& geom, 
		  I3OMResponseMap& ommap, 
		  const string hitseries,
		  double t1, 
		  double t2, 
		  int& Ndir, 
		  double& Ldir,
		  double& Sall,
		  double& Sdir);

  /**
   * A convenience function that calls DirectHits() and returns the number 
   * of direct hits from a given track.  If you are interested in more than 
   * one quantity from DirectHits(), use the DirectHits() function directly,
   * in order to save multiple calls to the function.
   */
  int Ndir(const I3Track& track, 
	   I3Geometry& geom, 
	   I3OMResponseMap& ommap, 
	   const string hitseries,
	   double t1 = minusTWindow, 
	   double t2 = plusTWindow);

  /**
   * A convenience function that calls DirectHits() and returns the 
   * "direct-hits length" of the event.  If you are interested in more than  
   * one quantity from DirectHits(), use the DirectHits() function directly, 
   * in order to save multiple calls to the function.
   */
  double Ldir(const I3Track& track, 
	      I3Geometry& geom, 
	      I3OMResponseMap& ommap, 
	      const string hitseries,
	      double t1 = minusTWindow, 
	      double t2 = plusTWindow);

  /**
   * A convenience function that calls DirectHits() and returns the 
   * "all-hits smoothness" of the event.  If you are interested in more than  
   * one quantity from DirectHits(), use the DirectHits() function directly, 
   * in order to save multiple calls to the function.
   */
  double SmoothnessAll(const I3Track& track, 
		       I3Geometry& geom, 
		       I3OMResponseMap& ommap, 
		       const string hitseries,
		       double t1 = minusTWindow, 
		       double t2 = plusTWindow);

  /**
   * A convenience function that calls DirectHits() and returns the 
   * "direct-hits smoothness" of the event.  If you are interested in more   
   * than one quantity from DirectHits(), use the DirectHits() function, 
   * directly in order to save multiple calls to the function.
   */
  double SmoothnessDir(const I3Track& track, 
		       I3Geometry& geom, 
		       I3OMResponseMap& ommap, 
		       const string hitseries,
		       double t1 = minusTWindow, 
		       double t2 = plusTWindow);



  // Computes the size of the "cylinder of closest approach", 
  // which is the amount by which one must expand a "reference cylinder"
  // (such as the volume of the in-ice detector) in order to just barely
  // contain the track.
  // For grusome defail, see Kath's thesis appendix A.
  //
  // "H0" = height of reference cylinder
  // "R0" = radius of reference cylinder
  // "center" = z-coordinate of center of reference cylinder
  //           (the x- and y-coordinates are assumed to be at zero)
  //
  // This is useful, for instance, for making cuts on whether a track goes
  // through the physical volume of the in-ice detector, close to the center,
  // or outside of it.
  double CylinderSize(const I3Track& track, 
		      double H0, 
		      double R0, 
		      double center);


}

#endif

