#include "phys-services/test-source/I3TestSource.h"

#include "dataclasses/I3Vector.h"
#include "dataclasses/physics/I3AMANDAAnalogReadout.h"
#include "dataclasses/physics/I3DOMLaunch.h"
#include "dataclasses/physics/I3MCHit.h"
#include "dataclasses/physics/I3RecoHit.h"
#include "dataclasses/physics/I3RecoPulse.h"
#include "dataclasses/physics/I3TWRLaunch.h"

template <> void I3TestSource<I3AMANDAAnalogReadout>::Randomize(I3AMANDAAnalogReadout& p){};
template <> void I3TestSource<I3DOMLaunch>::Randomize(I3DOMLaunch& p){};
template <> void I3TestSource<I3TWRLaunch>::Randomize(I3TWRLaunch& p){};
template <> void I3TestSource<I3Vector<I3MCHit> >::Randomize(I3Vector<I3MCHit>& p){};
template <> void I3TestSource<I3Vector<I3RecoHit> >::Randomize(I3Vector<I3RecoHit>& p){};
template <> void I3TestSource<I3Vector<I3RecoPulse> >::Randomize(I3Vector<I3RecoPulse>& p){};

template class I3TestSource<I3AMANDAAnalogReadout>;
template class I3TestSource<I3DOMLaunch>;
template class I3TestSource<I3TWRLaunch>;
template class I3TestSource<I3Vector<I3MCHit> >;
template class I3TestSource<I3Vector<I3RecoHit> >;
template class I3TestSource<I3Vector<I3RecoPulse> >;

I3_MODULE(I3TestSource<I3AMANDAAnalogReadout>);
I3_MODULE(I3TestSource<I3DOMLaunch>);
I3_MODULE(I3TestSource<I3TWRLaunch>);
I3_MODULE(I3TestSource<I3Vector<I3MCHit> >);
I3_MODULE(I3TestSource<I3Vector<I3RecoHit> >);
I3_MODULE(I3TestSource<I3Vector<I3RecoPulse> >);


