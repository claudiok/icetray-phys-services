/*
 * class: I3ContextAccess
 *
 * Version $Id: I3Context-I3ParticleDataService.cxx,v 1.1 2004/02/17 21:17:13 pretz Exp $
 *
 * Date: 29 Sept 2003
 *
 * (c) IceCube Collaboration
 */

// Header files
#include "icetray/I3ContextAccess.h"
#include "icetray/I3ServicesAccess.h"
#include "impl-icetray/I3ContextElement.h"
#include "impl-icetray/I3ContextElementFactory.h"
#include "phys-services/I3ParticleDataService.h"

ClassImpT(I3ContextAccess,Type);
ClassImpT(I3ServicesAccess,Type);
ClassImpT(I3ContextElement,Type);
ClassImpT(I3ContextElementFactory,Type)

template I3ContextAccess<I3ParticleDataService>;
template I3ServicesAccess<I3ParticleDataService>;
template I3ContextElement<I3ParticleDataService>;
template I3ContextElementFactory<I3ParticleDataService>;

const I3ContextElementFactory<I3ParticleDataService>* I3ContextElementFactory<I3ParticleDataService>::factoryImpl = 0;
