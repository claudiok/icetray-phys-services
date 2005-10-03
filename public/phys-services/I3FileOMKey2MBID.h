/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @file I3FileOMKey2MBID.h
 * @version $Revision:$
 * @date $Date$
 * @author pretz
 */

#ifndef I3FILEOMKEY2MBID_H
#define I3FILEOMKEY2MBID_H

#include "I3OMKey2MBID.h"

/**
 * @brief an implementation of I3OMKey2MBID that
 * reads the conversions from a file
 */
class I3FileOMKey2MBID : public I3OMKey2MBID
{
  map<OMKey,long long int> omkey2mbid_;
  map<long long int,OMKey> mbid2omkey_;
  
 public:
  /**
   * constructor takes the name of the input file.
   */
  I3FileOMKey2MBID(const string& infile);

  OMKey GetOMKey(long long int mbid);
  long long int GetMBID(OMKey key);

 private:
  OMKey OMKeyize(const string& key);

  void Fatal(const string& message);

  SET_LOGGER("I3FileOMKey2MBID");
};

#endif
