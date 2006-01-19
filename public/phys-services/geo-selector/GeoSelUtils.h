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

#ifndef I3GEOSELUTILITIES_H
#define I3GEOSELUTILITIES_H

/**
 * @brief Utilities for parsing the input parameters for I3GeometrySelector.
 */

#include <vector>
#include <string>

namespace geo_sel_utils{

  /**
   *Takes in two strings. (strings to use and strings to include)
   *The strings can take the form "i,j,n:m" (and any permutation) 
   *which would ex/include strings i,j, and n through m.
   */
  std::vector<int> make_good_strings(const std::string, const std::string);

  /**
   *checks whether an element (type T) exists in a vector
   *Returns true if it does, false otherwise
   */
  template <class T> bool exists(const T& , const std::vector<T>& );

  /**
   *checks whether an element (type T) exists in a vector
   *Returns a const_iterator (i.e. postion), which is equal to
   *'end' if the element doesn't exist
   */
  template <class T> typename std::vector<T>::const_iterator 
    exists_at(const T& , const std::vector<T>& );


  /**
   *Takes in a string of the form "i,j,n:m" and returns a vector
   *of integers whose elements are "i,j,n,n+1,n+2,...,m-1,m"
   */
  std::vector<int> parse_string_list(const std::string&);

  /**
   *Checks to see whether a string contains characters other than
   *signed integers, and the two delimiters used ',' and ':' 
   */
  bool good_input(const std::string& );
}

#endif
