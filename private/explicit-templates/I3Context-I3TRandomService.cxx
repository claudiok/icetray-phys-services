/*
 * class: I3ContextAccess
 *
 * Version $Id: I3Context-I3TRandomService.cxx,v 1.1 2004/02/19 13:31:35 pretz Exp $
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
#include "phys-services/I3TRandomService.h"

ClassImpT(I3ContextAccess,Type);
ClassImpT(I3ServicesAccess,Type);
ClassImpT(I3ContextElement,Type);
ClassImpT(I3ContextElementFactory,Type)

template I3ContextAccess<I3TRandomService>;
template I3ServicesAccess<I3TRandomService>;
template I3ContextElement<I3TRandomService>;
template I3ContextElementFactory<I3TRandomService>;

const I3ContextElementFactory<I3TRandomService>* I3ContextElementFactory<I3TRandomService>::factoryImpl = 0;
