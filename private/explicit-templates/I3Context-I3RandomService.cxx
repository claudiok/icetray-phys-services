/*
 * class: I3ContextAccess
 *
 * Version $Id: I3Context-I3RandomService.cxx,v 1.1 2004/02/19 22:53:34 pretz Exp $
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
#include "phys-services/I3RandomService.h"

ClassImpT(I3ContextAccess,Type);
ClassImpT(I3ServicesAccess,Type);
ClassImpT(I3ContextElement,Type);
ClassImpT(I3ContextElementFactory,Type)

template I3ContextAccess<I3RandomService>;
template I3ServicesAccess<I3RandomService>;
template I3ContextElement<I3RandomService>;
template I3ContextElementFactory<I3RandomService>;

const I3ContextElementFactory<I3RandomService>* I3ContextElementFactory<I3RandomService>::factoryImpl = 0;
