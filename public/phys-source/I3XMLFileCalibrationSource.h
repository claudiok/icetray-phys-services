#ifndef I3XMLFILECALIBRATIONSOURCE_H
#define I3XMLFILECALIBRATIONSOURCE_H

#include "I3CalibrationSource.h"

class I3XMLFileCalibrationSource : public I3CalibrationSource
{
public:
    I3XMLFileCalibrationSource(I3Context& context);

    CalibrationPair GetCalibration(I3Time eventTime);

    void Configure();

private:
    void FillCalibration(I3Calibration&, I3CalibrationHeader&);
    
    string ICCalibrationFile_;
};


#endif
