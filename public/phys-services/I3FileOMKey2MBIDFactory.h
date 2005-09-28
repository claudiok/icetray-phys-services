#ifndef I3FILEOMKEY2MBIDFACTORY_H
#define I3FILEOMKEY2MBIDFACTORY_H

class I3Context;
class I3Services;

#include "icetray/I3ServiceFactory.h"
#include "I3OMKey2MBID.h"

using namespace std;

class I3FileOMKey2MBIDFactory
: public I3ServiceFactory
{
 public:

  I3FileOMKey2MBIDFactory(const I3Context& context);

  virtual ~I3FileOMKey2MBIDFactory(){}

  bool InstallService(I3Services& services);

  void Configure();

 private:
  string infile_;

  I3OMKey2MBIDPtr service_;

  I3FileOMKey2MBIDFactory
    (const I3FileOMKey2MBIDFactory& rhs); 
  I3FileOMKey2MBIDFactory operator=
    (const I3FileOMKey2MBIDFactory& rhs); 

};

#endif 
