#ifndef I3FILEOMKEY2MBID_H
#define I3FILEOMKEY2MBID_H

#include "I3OMKey2MBID.h"

class I3FileOMKey2MBID : public I3OMKey2MBID
{
  map<OMKey,long long int> omkey2mbid_;
  map<long long int,OMKey> mbid2omkey_;
  
 public:
  I3FileOMKey2MBID(const string& infile);

  OMKey GetOMKey(long long int mbid);
  long long int GetMBID(OMKey key);

 private:
  OMKey OMKeyize(const string& key);

  void Fatal(const string& message);
};

#endif
