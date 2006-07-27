/*
 * $Id: I3Functions.cxx 4595 2005-04-13 16:29:34Z dule $
 * (c) 2005 IceCube Collaboration
 */

#ifndef I3FUNCTIONS_H
#define I3FUNCTIONS_H

#include <set>
#include <vector>
#include <string>
using namespace std;

namespace I3Functions
{

  /**
   * Function to parse a long string and divide it into its string constituents
   */
  set<string> ParseString(const string &bigString); 

  /**
   * Function to parse a long string of file name patterns, divide it into its string constituents, 
   * and search for matching file names
   */
  vector<string> ParseFilename(const string &bigFilename);
}

#endif
