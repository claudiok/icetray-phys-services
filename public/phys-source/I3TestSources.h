#ifndef I3TESTSOURCES_H_INCLUDED
#define I3TESTSOURCES_H_INCLUDED

#include "phys-services/I3PhysicsModule.h"

class I3TestSources : public I3PhysicsModule
{
public:
    SET_LOGGER("I3TestSources");
    
    I3TestSources(I3Context& ctx);
    ~I3TestSources();
    
    void Configure();

    void Calibration(I3Frame& frame);
    void Physics(I3Frame& frame);
    void DetectorStatus(I3Frame& frame);

private:
    I3TestSources();
    I3TestSources(const I3TestSources&);
    I3TestSources& operator=(const I3TestSources&);

    void DumpMCCascade(I3MCEvent*);
    void DumpGeometry(I3Geometry&);
    
    I3Position fCascadePositionTrue;

    ClassDef(I3TestSources, 0);
};


#endif //I3TESTSOURCES_H_INCLUDED
