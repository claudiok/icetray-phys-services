#ifndef I3OMKEY2MBID_H
#define I3OMKEY2MBID_H

#include "dataclasses/OMKey.h"

#include <map>

using namespace std;

class I3OMKey2MBID
{
 public:
  virtual ~I3OMKey2MBID(){}

  virtual OMKey GetOMKey(long long int mbid) = 0;
  virtual long long int GetMBID(OMKey key) = 0;

  static const char* DefaultName() { return "OMKey2MBID";}
};

typedef roost::shared_ptr<I3OMKey2MBID> I3OMKey2MBIDPtr;

#endif
