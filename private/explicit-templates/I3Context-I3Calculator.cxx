/*
 * class: I3ContextAccess
 *
 * Version $Id: I3Context-I3Calculator.cxx,v 1.1 2004/06/24 14:27:55 pretz Exp $
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
#include "phys-services/I3Calculator.h"

ClassImpT(I3ContextAccess,Type);
ClassImpT(I3ServicesAccess,Type);
ClassImpT(I3ContextElement,Type);
ClassImpT(I3ContextElementFactory,Type)

template I3ContextAccess<I3Calculator>;
template I3ServicesAccess<I3Calculator>;
template I3ContextElement<I3Calculator>;
template I3ContextElementFactory<I3Calculator>;

const I3ContextElementFactory<I3Calculator>* I3ContextElementFactory<I3Calculator>::factoryImpl = 0;
