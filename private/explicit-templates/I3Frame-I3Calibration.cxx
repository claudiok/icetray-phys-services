/*
 * class: I3Frame-I3Calibration
 * 
 * Version $Id: I3Frame-I3Calibration.cxx,v 1.1 2004/11/10 18:35:26 tmccauley Exp $
 *
 * Date: 10 October 2004
 *
 * (c) IceCube Collaboration
 */

#include "icetray/I3FrameAccess.h"
#include "impl-icetray/I3FrameElement.h"
#include "impl-icetray/I3FrameElementFactory.h"

#include "dataclasses/I3Calibration.h"

ClassImpT(I3FrameAccess,Type);
ClassImpT(I3FrameElement,Type);
ClassImpT(I3FrameElementFactory,Type);

template I3FrameAccess<I3Calibration>;
template I3FrameElement<I3Calibration>;
template I3FrameElementFactory<I3Calibration>;

const I3FrameElementFactory<I3Calibration>* I3FrameElementFactory<I3Calibration>::factoryImpl = 0;

