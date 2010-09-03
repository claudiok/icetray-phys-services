/**
 * copyright  (C) 2010
 * The Icecube Collaboration
 *
 * $Id$
 *
 * @version $Revision$
 * @date $LastChangedDate$
 * @author Fabian Kislat <fabian.kislat@desy.de> $LastChangedBy$
 */

#include "OMBlockConverter.h"
#include "phys-services/I3Calculator.h"
#include <dataclasses/geometry/I3Geometry.h>
#include <dataclasses/physics/I3Particle.h>
#include <dataclasses/physics/I3RecoPulse.h>


OMBlockConverter::OMBlockConverter()
  : reconstruction_(""), mc_(false)
{}

OMBlockConverter::OMBlockConverter(const std::string &reconstruction)
  : reconstruction_(reconstruction), mc_(false)
{}

OMBlockConverter::OMBlockConverter(const std::string &reconstruction, bool MC)
  : reconstruction_(reconstruction), mc_(MC)
{}

I3TableRowDescriptionPtr OMBlockConverter::CreateDescription(const I3RecoPulseSeriesMap &pulses)
{
  I3TableRowDescriptionPtr desc = I3TableRowDescriptionPtr(new I3TableRowDescription);
  desc->isMultiRow_ = true;

  desc->AddField<int8_t>("string", "", "String number");
  desc->AddField<uint8_t>("om", "", "OM number");

  desc->AddField<double>("x", "m", "X coordinate of the DOM");
  desc->AddField<double>("y", "m", "Y coordinate of the DOM");
  desc->AddField<double>("z", "m", "Z coordinate of the DOM");

  desc->AddField<double>("charge", "pe", "Pulse charge");
  desc->AddField<double>("time", "ns", "Pulse time");
  desc->AddField<double>("width", "ns", "Pulse width");
  
  if (reconstruction_.size() > 0) {
    desc->AddField<double>("DReco", "m", "Perpendicular distance to the reconstruction");
    desc->AddField<double>("ResReco", "ns", "Residual with respect to the reconstruction");
  }

  if (mc_) {
    desc->AddField<double>("DPrimary", "m", "Perpendicular distance to the primary");
    desc->AddField<double>("ResPrimary", "ns", "Residual with respect to the primary");
  }

  return desc;
}

size_t OMBlockConverter::FillRows(const I3RecoPulseSeriesMap &pulses, I3TableRowPtr rows)
{
  using I3Calculator::ClosestApproachDistance;
  using I3Calculator::TimeResidual;

  I3GeometryConstPtr geometry = currentFrame_->Get<I3GeometryConstPtr>();
  if (!geometry) {
    log_error("%s: No geometry in frame", __PRETTY_FUNCTION__);
    return 0;
  }

  I3ParticleConstPtr reco;
  if (reconstruction_.size() > 0) {
    reco = currentFrame_->Get<I3ParticleConstPtr>(reconstruction_);
    if (!reco) {
      log_warn("%s: Could not find I3Particle '%s' in frame.",
	       __PRETTY_FUNCTION__, reconstruction_.c_str());
    }
  }

  I3ParticleConstPtr primary;
  if (mc_) {
    primary = currentFrame_->Get<I3ParticleConstPtr>("MCPrimary");
    if (!primary) {
      log_warn("%s: No MCPrimary. Are you sure that this is MC?",
	       __PRETTY_FUNCTION__);
    }
  }


  I3RecoPulseSeriesMap::const_iterator iter;
  const size_t startRow = rows->GetCurrentRow();

  size_t currentRow;
  for (iter = pulses.begin(), currentRow = rows->GetCurrentRow(); 
       iter != pulses.end(); ++iter, ++currentRow)
    {
      rows->SetCurrentRow(currentRow);

      OMKey key = iter->first;
      I3OMGeoMap::const_iterator geoiter = geometry->omgeo.find(key);
      I3OMGeo omgeo;
      if (geoiter == geometry->omgeo.end()) {
	log_warn("%s: OMKey (%d,%d) not in geometry!", __PRETTY_FUNCTION__,
		 key.GetString(), key.GetOM());
      } else {
	omgeo = geoiter->second;
      }

      // /!\ only the first pulse is extracted!
      const I3RecoPulse &pulse = iter->second.front();
      rows->Set<int8_t>("string", key.GetString());
      rows->Set<uint8_t>("om", key.GetOM());

      rows->Set<double>("x", omgeo.position.GetX());
      rows->Set<double>("y", omgeo.position.GetY());
      rows->Set<double>("z", omgeo.position.GetZ());
      
      rows->Set<double>("charge", pulse.GetCharge());
      rows->Set<double>("time", pulse.GetTime()/I3Units::ns);
      rows->Set<double>("width", pulse.GetWidth()/I3Units::ns);

      if (reconstruction_.size() > 0) {
	if (reco) {
	  rows->Set<double>("DReco",
			    ClosestApproachDistance(*reco, omgeo.position));
	  rows->Set<double>("ResReco",
			    TimeResidual(*reco, omgeo.position, pulse.GetTime()));
	} else {
	  rows->Set<double>("DReco", NAN);
	  rows->Set<double>("ResReco", NAN);
	}
      }

      if (mc_) {
	if (primary) {
	  rows->Set<double>("DReco",
			    ClosestApproachDistance(*primary, omgeo.position));
	  rows->Set<double>("ResReco",
			    TimeResidual(*primary, omgeo.position,
					 pulse.GetTime()));
	} else {
	  rows->Set<double>("DPrimary", NAN);
	  rows->Set<double>("ResPrimary", NAN);
	}
      }
    }

  return currentRow - startRow;
}

size_t OMBlockConverter::GetNumberOfRows(const I3RecoPulseSeriesMap &pulses)
{
  return pulses.size();
}
