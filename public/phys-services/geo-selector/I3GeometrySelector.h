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

#ifndef I3GEOMETRYSELECTOR_H
#define I3GEOMETRYSELECTOR_H

#include "phys-services/I3PhysicsModule.h"

/**
 * @brief IceTray module that selects the strings to use.

 * This module has only two parameters "StringsToUse" and "StringsToExclude"
 * The default values for StringsToUse is the entire 80 string IceCube 
 * detector and AMANDA (i.e. "-19:80").  No strings are excluded by default.
 *
 * Examples values for the parameters are...
 *
 * 1) Use only the IceCube detector.
 * Either set StringsToUse to "1:80" or set StringsToExclude to "-19:0" 
 * (remember the default value for StringsToUse is "-19:80").
 *
 * 2) Use the current geometry (as of mid Jan '06).
 * Set StringsToUse to "21,29,30,38,39,-19:-1"
 */
class I3GeometrySelector : public I3PhysicsModule
{
public:

  /*
   * Constructor.
   */ 
  I3GeometrySelector(const I3Context& ctx);
  
  /*
   * Destructor.
   */ 
  ~I3GeometrySelector();
  
  /**
   * Checks the two parameters StringsToUse and StringsToExclude are valid.
   */
  void Configure();
  
  /** 
   * Gets the current geometry, constructs a new geometry based on the desired 
   * strings, and swaps them.
   */ 
  void Geometry(I3Frame& frame);

private:

  /**
   *default constructor, assignment operator, and copy constructor
   * declared private to prevent use
   */
  I3GeometrySelector();
  I3GeometrySelector(const I3GeometrySelector& source);
  I3GeometrySelector& operator=(const I3GeometrySelector& source);

  /**
   * Parameter - The strings to use.
   * Default value is "-19:80".
   */
  string stringsToUse_;

  /**
   * Parameter - The strings to exclude.
   * Default value is NULL.
   */
  string stringsToExclude_;

  /**
   * A list of strings to use.  This vector is constructed from the input parameters
   * StringsToUse and StringsToExclude.
   */
  vector<int> goodStrings_;

  SET_LOGGER("I3GeometrySelector");
  
};  // end of class I3GeometrySelector

#endif //I3GEOMETRYSELECTOR_H
