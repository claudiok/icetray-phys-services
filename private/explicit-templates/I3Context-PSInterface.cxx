/*
 * class: I3ContextAccess
 *
 * Version $Id: I3Context-PSInterface.cxx,v 1.1 2004/02/20 15:00:38 pretz Exp $
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
#include "PSInterface.h"

ClassImpT(I3ContextAccess,Type);
ClassImpT(I3ServicesAccess,Type);
ClassImpT(I3ContextElement,Type);
ClassImpT(I3ContextElementFactory,Type)

template I3ContextAccess<PSInterface>;
template I3ServicesAccess<PSInterface>;
template I3ContextElement<PSInterface>;
template I3ContextElementFactory<PSInterface>;

const I3ContextElementFactory<PSInterface>* I3ContextElementFactory<PSInterface>::factoryImpl = 0;
