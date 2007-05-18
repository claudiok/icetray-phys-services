/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3StringAdderService.h 15038 2006-01-30 22:47:23Z pretz $
 *
 * @file I3StringAdderService.h
 * @version $Revision:$
 * @date $Date: 2006-01-30 17:47:23 -0500 (Mon, 30 Jan 2006) $
 * @author olivas
 */

#ifndef I3STRINGADDER_H
#define I3STRINGADDER_H

#include <string>
#include <fstream>
#include <boost/shared_ptr.hpp>
#include <phys-services/I3GeometryService.h>
#include "icetray/I3Context.h"

using namespace std;

/**
 * @brief A I3GeometryOrigin which reads the default geometry and serves up a reduced geometry.
 */
class I3StringAdderService : public I3GeometryService
{

  SET_LOGGER("I3StringAdderService");

  double domSpacing_;

  unsigned int domsPerString_;

  vector<I3OMGeo> omGeoList_;

  I3GeometryServicePtr geo_service_;

 public:
  I3StringAdderService(I3GeometryServicePtr g){
    geo_service_ = g;
  }

  virtual ~I3StringAdderService(){}

  I3GeometryConstPtr GetGeometry(I3Time time);

  void SetDOMSpacing(double s){ domSpacing_ = s; }

  double GetDOMSpacing(){ return domSpacing_; }

  void SetNDOMsPerString(unsigned int n){ domsPerString_ = n; };

  unsigned int GetNDOMsPerString(){ return domsPerString_; }

  void SetOMGeoList(vector<I3OMGeo>& v){ omGeoList_ = v; }

  const vector<I3OMGeo>& GetOMGeoList() const { return omGeoList_; }
};

I3_POINTER_TYPEDEFS(I3StringAdderService);

#endif
