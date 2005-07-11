#ifndef I3XMLFILEDETECTORSTATUSSOURCE_H
#define I3XMLFILEDETECTORSTATUSSOURCE_H

#include "I3DetectorStatusSource.h"

class I3XMLFileDetectorStatusSource : public I3DetectorStatusSource
{
public:
    I3XMLFileDetectorStatusSource(I3Context& context);

    DetectorStatusPair GetDetectorStatus(I3Time eventTime);

    void Configure();
    

private:
    void FillDetectorStatus(I3DetectorStatus&, I3DetectorStatusHeader&);
    
    string ICDetectorStatusFile_;
};


#endif
