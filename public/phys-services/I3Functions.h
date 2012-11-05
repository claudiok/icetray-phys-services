/*
 * $Id: I3Functions.cxx 4595 2005-04-13 16:29:34Z dule $
 * (c) 2005 IceCube Collaboration
 */

#ifndef I3FUNCTIONS_H
#define I3FUNCTIONS_H

#include <set>
#include <vector>
#include <string>

namespace I3Functions
{

  /**
   * Function to parse a long string and divide it into its string constituents
   */
  std::set<std::string> ParseString(const std::string &bigString); 

  /**
   * Function to parse a long string of file name patterns, divide it into its string constituents, 
   * and search for matching file names
   */
  std::vector<std::string> ParseFilename(const std::string &bigFilename);
}

#endif
