/**
 * copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Jakob van Santen <vansanten@wisc.edu> Last changed by: $LastChangedBy$
 */

#include <icetray/I3Module.h>
#include <icetray/I3DefaultName.h>
#include <interfaces/I3EventService.h>

class I3FrameDiff : public I3Module {
	I3EventServicePtr diffService_;
	std::string diffServiceName_;
public:
	I3FrameDiff(const I3Context &);
	
	void Configure();
	
	void Physics(I3FramePtr);
};

I3_MODULE(I3FrameDiff);

I3FrameDiff::I3FrameDiff(const I3Context &ctx) : I3Module(ctx)
{
	diffServiceName_ = I3DefaultName<I3EventService>::value();
	AddParameter("DiffService",
	    "Name of the service that implements DiffEvent().",
	    diffServiceName_);
	
	AddOutBox("OutBox");
}

void
I3FrameDiff::Configure()
{
	GetParameter("DiffService", diffServiceName_);
	
	diffService_ = context_.Get<I3EventServicePtr>(diffServiceName_);
	
	if (!diffService_)
		log_fatal("The service '%s' won't cast to I3EventService!",
		    diffServiceName_.c_str());
	if (!diffService_->DiffEventImplemented())
		log_fatal("The service '%s' doesn't implement DiffEvent()!",
		    diffServiceName_.c_str());
}

void
I3FrameDiff::Physics(I3FramePtr frame)
{
	diffService_->DiffEvent(*frame);
	PushFrame(frame, "OutBox");
}
