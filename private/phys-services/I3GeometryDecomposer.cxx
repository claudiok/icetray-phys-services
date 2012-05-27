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
#include <dataclasses/geometry/I3ModuleGeo.h>
#include <dataclasses/I3Time.h>
#include <dataclasses/I3Double.h>

#include <boost/foreach.hpp>

/**
 * @brief Splits an I3Geometry object into its
 * components (I3OMGeoMap, I3StationGeoMap and
 * I3Time) and stores them in the Geometry frame.
 *
 * While at it, this also generates an I3ModuleGeoMap
 * assuming that all existing DOMs are IceCube
 * single-PMT DOMs.
 */
class I3GeometryDecomposer : public I3Module
{
public:
    I3GeometryDecomposer(const I3Context& context);
    void Configure();
    void Geometry(I3FramePtr frame);
    
private:
    bool deleteI3Geometry_;
    
    I3ModuleGeoMapPtr
    GenerateI3ModuleGeo(const I3OMGeoMap &omgeo) const;

    I3MapModuleKeyStringPtr
    GenerateSubdetectorMap(const I3OMGeoMap &omgeo) const;
};

I3_MODULE(I3GeometryDecomposer);

I3GeometryDecomposer::I3GeometryDecomposer(const I3Context& context)
:
I3Module(context),
deleteI3Geometry_(false)
{
    AddParameter("DeleteI3Geometry",
                 "Get rid of the original I3Geometry object.",
                 deleteI3Geometry_);
    AddOutBox("OutBox");
}

void
I3GeometryDecomposer::Configure()
{
    GetParameter("DeleteI3Geometry", deleteI3Geometry_);
}

void
I3GeometryDecomposer::Geometry(I3FramePtr frame)
{
    I3GeometryConstPtr geometry = frame->Get<I3GeometryConstPtr>();

    if (!geometry)
        log_fatal("There is no I3Geometry object in the Geometry frame!");

    frame->Put("I3OMGeoMap",      I3OMGeoMapPtr     (new I3OMGeoMap     (geometry->omgeo     )));
    frame->Put("I3ModuleGeoMap",  GenerateI3ModuleGeo(geometry->omgeo));
    frame->Put("I3StationGeoMap", I3StationGeoMapPtr(new I3StationGeoMap(geometry->stationgeo)));
    frame->Put("StartTime",     I3TimePtr         (new I3Time         (geometry->startTime )));
    frame->Put("EndTime",       I3TimePtr         (new I3Time         (geometry->endTime   )));

    frame->Put("Subdetectors",  GenerateSubdetectorMap(geometry->omgeo));

    
    const double bedrockDepth = 2810.*I3Units::m;
    const double icecubeCenterDepth = 1948.07*I3Units::m;
    
    // assume this is IceCube
    frame->Put("BedrockZ",        I3DoublePtr       (new I3Double       (icecubeCenterDepth-bedrockDepth)));
    frame->Put("DepthAtZ0",       I3DoublePtr       (new I3Double       (icecubeCenterDepth   )));

    if (deleteI3Geometry_) {
        frame->Delete(I3DefaultName<I3Geometry>::value());
    }
    
    PushFrame(frame);
}

/**
 * distinguish between IceCube, IceTop and DeepCore by string number only
 */
I3MapModuleKeyStringPtr
I3GeometryDecomposer::GenerateSubdetectorMap(const I3OMGeoMap &omgeo) const
{
    I3MapModuleKeyStringPtr output(new I3MapModuleKeyString());
    
    BOOST_FOREACH(const I3OMGeoMap::value_type &pair, omgeo)
    {
        const OMKey &input_key = pair.first;
        if (input_key.GetPMT() != 0) {
            log_fatal("You seem to be using a non-IceCube I3Geometry object with non-zero PMT ids (pmtid=%u). Cannot convert this.",
                      static_cast<unsigned int>(input_key.GetPMT()));
        }

        const ModuleKey key(input_key.GetString(), input_key.GetOM());
        
        if (key.GetString() < 0) {
            (*output)[key] = "AMANDA";
            continue;
        }

        if (key.GetString() == 0)
            log_fatal("This module assumes an IceCube geometry as input. It may not contain string number 0!");
        
        if (key.GetOM() > 60) {
            (*output)[key] = "IceTop";
            continue;
        }

        if (key.GetString() >= 79) {
            (*output)[key] = "DeepCore";
            continue;
        }
        
        (*output)[key] = "IceCube";
    }
    
    return output;
}

/**
 * @brief Generates an I3ModuleGeoMap from a I3OMGeoMap,
 * assuming this is an IceCube-DOM-only geometry.
 */
I3ModuleGeoMapPtr
I3GeometryDecomposer::GenerateI3ModuleGeo(const I3OMGeoMap &omgeo) const
{
    I3ModuleGeoMapPtr output(new I3ModuleGeoMap());
                       
    BOOST_FOREACH(const I3OMGeoMap::value_type &pair, omgeo)
    {
        const OMKey &input_key = pair.first;
        const I3OMGeo &input_geo = pair.second;

        const ModuleKey output_key(input_key.GetString(), input_key.GetOM());

        if (input_key.GetPMT() != 0) {
            log_fatal("You seem to be using a non-IceCube I3Geometry object with non-zero PMT ids (pmtid=%u). Cannot convert this.",
                      static_cast<unsigned int>(input_key.GetPMT()));
        }
        
        if (output->find(output_key) != output->end()) {
            log_fatal("Logic error. output ModuleKey(%i,%u) is already in output map.",
                      output_key.GetString(), output_key.GetOM());
        }
        
        // insert empty object into output map and retrieve reference
        I3ModuleGeo &output_geo =
        output->insert(std::make_pair(output_key, I3ModuleGeo())).first->second;
        
        switch (input_geo.omtype) {
            case I3OMGeo::UnknownType: output_geo.SetModuleType(I3ModuleGeo::UnknownType); break;
            case I3OMGeo::AMANDA:      output_geo.SetModuleType(I3ModuleGeo::AMANDA);      break;
            case I3OMGeo::IceCube:     output_geo.SetModuleType(I3ModuleGeo::IceCube);     break;
            case I3OMGeo::IceTop:      output_geo.SetModuleType(I3ModuleGeo::IceTop);      break;
            default:
                log_error("Unknown input OMType number %u. Using I3ModuleGeo::ModuleType \"Unknown\".",
                          static_cast<unsigned int>(input_geo.omtype));
                output_geo.SetModuleType(I3ModuleGeo::UnknownType);
                break;
        }
        
        output_geo.SetPos(input_geo.position);
        output_geo.SetOrientation(input_geo.orientation);
        
        output_geo.SetRadius((13./2.)*25.4*I3Units::mm); // assume 13" diameter
    }
    
    return output;
}
