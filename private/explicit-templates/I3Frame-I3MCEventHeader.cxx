/*
 * class: I3FrameAccess
 *
 * Version $Id: I3Frame-I3MCEventHeader.cxx,v 1.1 2004/08/06 15:12:57 pretz Exp $
 *
 * Date: 29 Sept 2003
 *
 * (c) IceCube Collaboration
 */

// Header files
#include "icetray/I3FrameAccess.h"
#include "impl-icetray/I3FrameElement.h"
#include "impl-icetray/I3FrameElementFactory.h"

#include "dataclasses/I3MCEventHeader.h"

ClassImpT(I3FrameAccess,Type);
ClassImpT(I3FrameElement,Type);
ClassImpT(I3FrameElementFactory,Type)

template I3FrameAccess<I3MCEventHeader>;
template I3FrameElement<I3MCEventHeader>;
template I3FrameElementFactory<I3MCEventHeader>;

const I3FrameElementFactory<I3MCEventHeader>* I3FrameElementFactory<I3MCEventHeader>::factoryImpl = 0;
