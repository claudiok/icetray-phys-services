/**
 * copyright  (C) 2004
 * the IceCube collaboration
 *  $Id: I3Selection.h 2601 2005-02-08 20:05:42Z olivas $
  *
 * @file I3Selection.h
 * @version $Revision: 1.3 $
 * @date $Date: 2005-02-08 21:05:42 +0100 (Tue, 08 Feb 2005) $
 * @author olivas
 */

#ifndef GEOSELTESTMODULE_H
#define GEOSELTESTMODULE_H

// header files
#include "phys-services/I3PhysicsModule.h"

/**
 * @brief IceTray module to test whether I3GeometrySelector is working properly.
 *The two parameters stringsToUse_ and stringsToExclude_ should be set to the same 
 *values as the I3GeometrySelector.  This test passes if the geometry contains only OMs
 *that are in stringsToUse_ and does not contain any DOMs that are in stringsToExclude_.
 */

class I3GeoSelTestModule : public I3PhysicsModule
{
public:

  /*
   * Constructor:  builds an instance of the module, with the
   * context provided by IceTray. 
   */ 
  I3GeoSelTestModule(const I3Context& ctx);
  
  /*
   * Destructor: deletes the module
   */ 
  ~I3GeoSelTestModule();
  
  /**
   * This module takes a configuration parameter and so it must be configured
   */
  void Configure();
  
  /** 
   * We'll want to trim the geometry everytime it gets updated.
   */ 
  void Geometry(I3Frame& frame);

private:
  
  /**
   *default constructor, assignment operator, and copy constructor
   * declared private to prevent use
   */
  I3GeoSelTestModule();
  I3GeoSelTestModule(const I3GeoSelTestModule& source);
  I3GeoSelTestModule& operator=(const I3GeoSelTestModule& source);

  /**
   *Takes the form of "i,j,n:m" and this will use strings i,j,n,n+1,...,m-1,m
   */
  string stringsToUse_;

  /**
   *Takes the form of "i,j,n:m" and this will exclude strings i,j,n,n+1,...,m-1,m
   */
  string stringsToExclude_;

  /**
   *This is the list of strings to use
   */
  vector<int> goodStrings_;

  // Named stream for my logging messages.  Allows my messages to be
  // sent to a particular log file, to be set to a special threshold, etc.
  SET_LOGGER("I3GeoSelTestModule");
  
};  // end of class I3Selection

#endif //I3GEOSELTESTMODULE_H