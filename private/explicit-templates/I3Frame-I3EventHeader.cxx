/*
 * class: I3FrameAccess
 *
 * Version $Id: I3Frame-I3EventHeader.cxx,v 1.1 2004/08/06 14:56:02 pretz Exp $
 *
 * Date: 29 Sept 2003
 *
 * (c) IceCube Collaboration
 */

// Header files
#include "icetray/I3FrameAccess.h"
#include "impl-icetray/I3FrameElement.h"
#include "impl-icetray/I3FrameElementFactory.h"

#include "dataclasses/I3EventHeader.h"

ClassImpT(I3FrameAccess,Type);
ClassImpT(I3FrameElement,Type);
ClassImpT(I3FrameElementFactory,Type)

template I3FrameAccess<I3EventHeader>;
template I3FrameElement<I3EventHeader>;
template I3FrameElementFactory<I3EventHeader>;

const I3FrameElementFactory<I3EventHeader>* I3FrameElementFactory<I3EventHeader>::factoryImpl = 0;
