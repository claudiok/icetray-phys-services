#include "phys-services/I3XMLOMKey2MBID.h"

namespace bp = boost::python;

void register_I3XMLOMKey2MBID()
{
	bp::class_<I3XMLOMKey2MBID, boost::noncopyable>("I3XMLOMKey2MBID", bp::no_init)
		.def("Dump", &I3XMLOMKey2MBID::Dump)
		.staticmethod("Dump")
	;
}
