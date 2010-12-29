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

namespace bp = boost::python;

#include "phys-services/source/I3Muxer.h"

#include <icetray/I3Context.h>
#include <icetray/I3Frame.h>
#include <icetray/I3Configuration.h>

void
register_I3Muxer()
{	
	bp::class_<I3Muxer, boost::shared_ptr<I3Muxer>, boost::noncopyable>("I3MuxerModule", bp::init<const I3Context&>())
		.def("PopFrame", &I3Muxer::PopFrame)
		.def("Configure", &I3Muxer::Configure)
		;
}