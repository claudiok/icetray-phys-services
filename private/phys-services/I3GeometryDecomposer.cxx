/**
 *  $Id$
 *  
 *  Copyright (C) 2012
 *  Claudio Kopper <ckopper@icecube.wisc.edu>
 *  and the IceCube Collaboration <http://www.icecube.wisc.edu>
 *  
 */

#include <icetray/I3Module.h>
#include <icetray/I3Units.h>
#include <dataclasses/geometry/I3Geometry.h>
#include <dataclasses/geometry/I3OMGeo.h>
#include <dataclasses/geometry/I3TankGeo.h>
#include <dataclasses/I3Time.h>

#include <boost/foreach.hpp>

/**
 * @brief Splits an I3Geometry object into its
 * components (I3OMGeoMap, I3StationGeoMap and
 * I3Time) and stores them in the Geometry frame.
 *
 */
class I3GeometryDecomposer : public I3Module
{
public:
    I3GeometryDecomposer(const I3Context& context);
    void Configure();
    void Geometry(I3FramePtr frame);
};

I3_MODULE(I3GeometryDecomposer);

I3GeometryDecomposer::I3GeometryDecomposer(const I3Context& context)
:
I3Module(context)
{
    AddOutBox("OutBox");
}

void
I3GeometryDecomposer::Configure()
{
}

void
I3GeometryDecomposer::Geometry(I3FramePtr frame)
{
    I3GeometryConstPtr geometry = frame->Get<I3GeometryConstPtr>();

    if (!geometry)
        log_fatal("There is no I3Geometry object in the Geometry frame!");

    frame->Put("I3OMGeoMap",      I3OMGeoMapPtr     (new I3OMGeoMap     (geometry->omgeo     )));
    frame->Put("I3StationGeoMap", I3StationGeoMapPtr(new I3StationGeoMap(geometry->stationgeo)));
    frame->Put("StartTime",       I3TimePtr         (new I3Time         (geometry->startTime )));
    frame->Put("EndTime",         I3TimePtr         (new I3Time         (geometry->endTime   )));

    PushFrame(frame);
}
