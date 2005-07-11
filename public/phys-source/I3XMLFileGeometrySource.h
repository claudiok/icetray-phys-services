#ifndef I3XMLFILEGEOMETRYSOURCE_H
#define I3XMLFILEGEOMETRYSOURCE_H

#include "phys-source/I3GeometrySource.h"

class I3XMLFileGeometrySource : public I3GeometrySource
{
public:
    I3XMLFileGeometrySource(I3Context& context);

    void Configure();

    GeometryPair GetGeometry(I3Time eventTime);

private:
    void FillGeometry(I3Geometry&, I3GeometryHeader&);
    
    string ICGeometryFile_;
};

#endif
