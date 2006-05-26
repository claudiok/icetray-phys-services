/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3GeometrySelectorService.h 15038 2006-01-30 22:47:23Z pretz $
 *
 * @file I3GeometrySelectorService.h
 * @version $Revision:$
 * @date $Date: 2006-01-30 17:47:23 -0500 (Mon, 30 Jan 2006) $
 * @author olivas
 */

#ifndef I3GEOMETRYSELECTORSERVICE_H
#define I3GEOMETRYSELECTORSERVICE_H

#include <string>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <phys-services/I3GeometryService.h>
#include "icetray/I3Context.h"

using namespace std;

/**
 * @brief A I3GeometryOrigin which reads the default geometry and serves up a reduced geometry.
 */
class I3GeometrySelectorService : public I3GeometryService
{
  /**
   * A list of strings to use.  This vector is constructed from the input parameters
   * StringsToUse and StringsToExclude.
   */
  vector<int> goodStrings_;

  /**
   * A list of strings to use.  This vector is constructed from the input parameters
   * StringsToUse and StringsToExclude.
   */
  vector<int> goodStations_;

  I3GeometryServicePtr geo_service_;
 public:
  I3GeometrySelectorService(I3GeometryServicePtr g) 
     {geo_service_ = g; }

  void SetGoodStrings(vector<int>& v){goodStrings_ = v; };
  void SetGoodStations(vector<int>& v){goodStations_ = v; };

  virtual ~I3GeometrySelectorService(){}

  I3GeometryConstPtr GetGeometry(I3Time time);
 private:
};

I3_POINTER_TYPEDEFS(I3GeometrySelectorService);

#endif
