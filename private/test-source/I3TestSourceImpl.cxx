#include "phys-services/test-source/I3TestSource.h"
#include "dataclasses/physics/I3Particle.h"

template <> void I3TestSource<I3Particle>::Randomize(I3Particle& p){

}

I3_MODULE(I3TestSource<I3Particle>);
template class I3TestSource<I3Particle>;
