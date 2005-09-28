#ifndef I3TEXTFILEGEOMETRYSOURCE_H
#define I3TEXTFILEGEOMETRYSOURCE_H

#include "phys-source/I3GeometrySource.h"

class I3TextFileGeometrySource : public I3GeometrySource
{
public:
    I3TextFileGeometrySource(const I3Context& context);

    void Configure();

    GeometryPair GetGeometry(I3Time eventTime);

private:
    void FillGeometry(I3Geometry&, 
		 I3GeometryHeader&);
    
    string amaGeoFile_;
    string icecubeGeoFile_;
};

#endif
