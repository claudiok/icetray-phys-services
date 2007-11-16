/**
 *  copyright  (C) 2007
 *  the icecube collaboration
 *  $Id$
 *
 *  @file
 *  @version $Revision$
 *  @date $Date$
 *  @author David Boersma <boersma@icecube.wisc.edu>
 */

// for std::pair
#include <utility>
#include <map>

#include "phys-services/geo-selector/I3GeoTrimmers.h"
#include "Miniball.h"

I3OMGeoMapPtr I3GeoTrimmers::GetMinBallGeometry( const I3OMGeoMap &input_geo,
                                                 const I3OMGeoMap &subgeo,
                                                 double margin ){


  // storing lowest and highest 
  std::map<int,int> topOMs;
  std::map<int,int> botOMs;
  std::map<int,int>::iterator itop;
  std::map<int,int>::iterator ibot;
  I3OMGeoMap::const_iterator igeo;
  int Nused = 0;
  for ( igeo = subgeo.begin(); igeo != subgeo.end(); igeo++ ){
    int istr = igeo->first.GetString();
    int iom = igeo->first.GetOM();
    if ( (itop = topOMs.find(istr)) == topOMs.end() ){
      topOMs[istr] = iom;
      botOMs[istr] = iom;
      ++Nused;
    } else {
      ibot = botOMs.find(istr);
      if ( itop->second == ibot->second ){
        ++Nused;
      }
      if ( itop->second < iom ){
        itop->second = iom;
      }
      if ( ibot->second > iom ){
        ibot->second = iom;
      }
    }
  }
  log_debug( "input geo with %zu entries, subgeo with %zu entries",
             input_geo.size(), subgeo.size() );
  log_debug( "%d DOMs are used to find the minimum ball", Nused );

  // Use Bernd Gaertner's minimum ball code.
  // Fill the ball with the positions of the highest and lowest hit
  // DOMs on each string.
  miniball::Miniball<3> ballmaker;
  miniball::Point<3> p;
  for ( itop = topOMs.begin(); itop != topOMs.end(); ++itop ){
    int str = itop->first;
    ibot = botOMs.find(itop->first);
    int top = itop->second;
    int bot = ibot->second;
    if ( bot == top ){
      const I3Position &pos = subgeo.find(OMKey(str,top))->second.position;
      p[0] = pos.GetX();
      p[1] = pos.GetY();
      p[2] = pos.GetZ();
      ballmaker.check_in(p);
    } else {
      const I3Position &tpos = subgeo.find(OMKey(str,top))->second.position;
      p[0] = tpos.GetX();
      p[1] = tpos.GetY();
      p[2] = tpos.GetZ();
      ballmaker.check_in(p);
      const I3Position &bpos = subgeo.find(OMKey(str,bot))->second.position;
      p[0] = bpos.GetX();
      p[1] = bpos.GetY();
      p[2] = bpos.GetZ();
      ballmaker.check_in(p);
    }
  }
  log_debug("going to search minimum ball...");
  ballmaker.build();
  log_debug("done!");
  miniball::Point<3> center = ballmaker.center();
  double radius2 = ballmaker.squared_radius();
  double radius = sqrt(radius2) + margin;
  log_debug( "Center=(%.1f,%.1f,%.1f), r=%.3f (margin=%.3f)",
             center[0], center[1], center[2], radius, margin );
  if ( margin > 0 ){
    radius2 = radius * radius;
  }

  log_debug("now generating ball geo");
  I3OMGeoMapPtr ballmap( new I3OMGeoMap );
  for ( igeo = input_geo.begin(); igeo != input_geo.end(); ++igeo ){
    const I3Position &pos = igeo->second.position;
    double dx = pos.GetX() - center[0];
    double dy = pos.GetY() - center[1];
    double dz = pos.GetZ() - center[2];
    if ( dx*dx + dy*dy + dz*dz <= radius2 ){
      ballmap->insert(make_pair(igeo->first,igeo->second));
    }
  }
  log_debug("ball geo has %zu entries", ballmap->size() );

  return ballmap;
}
