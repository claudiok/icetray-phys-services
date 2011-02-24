/**
 *  $Id$
 *  
 *  Copyright (C) 2011
 *  Nathan Whitehorn <nwhitehorn@icecube.wisc.edu>
 *  and the IceCube Collaboration <http://www.icecube.wisc.edu>
 *  
 */

#include <icetray/I3Module.h>
#include <phys-services/I3Splitter.h>

class I3NullSplitter : public I3Module, public I3Splitter
{
	public:
		I3NullSplitter(const I3Context& context);
		void DAQ(I3FramePtr frame);
};

I3_MODULE(I3NullSplitter);

I3NullSplitter::I3NullSplitter(const I3Context& context) :
  I3Module(context), I3Splitter(context) {
	AddOutBox("OutBox");
}

void
I3NullSplitter::DAQ(I3FramePtr frame) {
	PushFrame(frame);
	PushFrame(GetNextSubEvent(frame));
}

