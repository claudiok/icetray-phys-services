#include "phys-services/I3ParticleDataService.h"

#include "dataclasses/I3Units.h"
#include <climits>
#include <string>
#include <cstdio>

ClassImp(I3ParticleDataService);

I3ParticleDataService::I3ParticleDataService() 
{
}

I3ParticleDataService::~I3ParticleDataService()
{
}

I3Track::Type I3ParticleDataService::TranslateFromF2k(Int_t f2kid)
{
  return f2kid;
}

I3Track::Type I3ParticleDataService::TranslateFromString(const Char_t* name)
{
  return I3Track::Unknown;
}

I3Track::Type I3ParticleDataService::TranslateFromPDG(Int_t pdgid)
{
  return I3Track::Unknown;
}

I3Track::Type I3ParticleDataService::TranslateFromCorsika(Int_t corsika_id)
{
  return I3Track::Unknown;
}

Double_t I3ParticleDataService::Mass(I3Track::Type type)
{
  if(type ==I3Track::Null)
    return -1.0;
  else if(type == I3Track::Unknown)
    return -1.0;
  else if(type == I3Track::Gamma)
    return 0.0;
  else if(type == I3Track::EPlus)
    return 510.9989 * I3Units::keV;
  else if(type == I3Track::EMinus)
    return 510.9989 * I3Units::keV;
  else if(type == I3Track::Nu)
    return 0.0;  // check back with Super K.
  else if(type == I3Track::MuPlus)
    return 105.568357 * I3Units::MeV;
  else if(type == I3Track::MuMinus)
    return 105.568357 * I3Units::MeV;
  else if(type == I3Track::Pi0)
    return 134.9766 * I3Units::MeV;
  else if(type == I3Track::PiPlus)
    return 139.57018 * I3Units::MeV;
  else if(type == I3Track::PiMinus)
    return 139.57018 * I3Units::MeV;
  else if(type == I3Track::PPlus)
    return 938.27200 * I3Units::MeV;
  else if(type == I3Track::PMinus)
    return 938.27200 * I3Units::MeV;
  else if(type == I3Track::TauPlus)
    return 1776.99 * I3Units::MeV;
  else if(type == I3Track::TauMinus)
    return 1776.99 * I3Units::MeV;
  else if(type == I3Track::NuE)
    return 0.0;  
  else if(type == I3Track::NuMu)
    return 0.0;
  else if(type == I3Track::NuTau)
    return 0.0;
  else if(type == I3Track::NuEBar)
    return 0.0;
  else if(type == I3Track::NuMuBar)
    return 0.0;
  else if(type == I3Track::Brems)
    return -1.0;  // What goes here????
  else if(type == I3Track::DeltaE)
    return -1.0;  // what goes here????
  else if(type == I3Track::PairProd)
    return -1.0;  // what goes here????
  else if(type == I3Track::NuclInt)
    return -1.0 ; // what goes here????
  else if(type == I3Track::MuPair)
    return -1.0;  // what goes here????
  else if(type == I3Track::Hadrons)
    return -1.0;  // what goes here????
  else if(type == I3Track::FiberLaser)
    return 0.0;   // it's just a photon, right
  else if(type == I3Track::N2Laser)
    return 0.0;   // just a photon, right?
  else if(type == I3Track::YAGLaser)
    return 0.0;
  else if(type >= I3Track::ZPrimary && type <=I3Track::ZPrimary+400)
    {
      // don't know what to do here, so just approximated
      // 2 * mass proton * Z of particle.  
      return 2 * 938 * I3Units::MeV * (type - I3Track::ZPrimary) ;
    }
  else if(type >= I3Track::APrimary && type <= I3Track::APrimary+400)
    {
      // don't know what to do here, so just approximated
      // just say 2 * mass proton * A of the particle
      return 2 * 938 * I3Units::MeV * ( type - I3Track::APrimary );
    }
  else if(type == I3Track::Elph)
    // A rough approximation (I guess we'll have to wait for LHC to be sure):
    // 6 tons = 12000 lbs ~ 5500 kg = 5500 c * c  J/c^2 = 4.95e20 J/c^2 
    return 4.95e20 * I3Units::joule;

  return -1.0;
}

Double_t I3ParticleDataService::LifeTime(I3Track::Type type)
{
  if(type ==I3Track::Null)
    return -1.0;
  else if(type == I3Track::Unknown)
    return -1.0;
  else if(type == I3Track::Gamma)
    return -1.0;
  else if(type == I3Track::EPlus)
    return -1.0;
  else if(type == I3Track::EMinus)
    return -1.0;
  else if(type == I3Track::Nu)
    return -1.0;  // check back with Super K.
  else if(type == I3Track::MuPlus)
    return 2197.03 * I3Units::ns;
  else if(type == I3Track::MuMinus)
    return 2197.03 * I3Units::ns;
  else if(type == I3Track::Pi0)
    return 8.4e-17 * I3Units::s;
  else if(type == I3Track::PiPlus)
    return 2.6033e-8 * I3Units::s;
  else if(type == I3Track::PiMinus)
    return 2.6033e-8 * I3Units::s;
  else if(type == I3Track::PPlus)
    return -1.0;
  else if(type == I3Track::PMinus)
    return -1.0;
  else if(type == I3Track::TauPlus)
    return 290.6e-15 * I3Units::s;
  else if(type == I3Track::TauMinus)
    return 290.6e-15 * I3Units::s;
  else if(type == I3Track::NuE)
    return -1.0;
  else if(type == I3Track::NuMu)
    return -1.0;
  else if(type == I3Track::NuTau)
    return -1.0;
  else if(type == I3Track::NuEBar)
    return -1.0;
  else if(type == I3Track::NuMuBar)
    return -1.0;
  else if(type == I3Track::Brems)
    return -1.0;  // What goes here????
  else if(type == I3Track::DeltaE)
    return -1.0;  // what goes here????
  else if(type == I3Track::PairProd)
    return -1.0;  // what goes here????
  else if(type == I3Track::NuclInt)
    return -1.0 ; // what goes here????
  else if(type == I3Track::MuPair)
    return -1.0;  // what goes here????
  else if(type == I3Track::Hadrons)
    return -1.0;  // what goes here????
  else if(type == I3Track::FiberLaser)
    return -1.0;   // it's just a photon, right
  else if(type == I3Track::N2Laser)
    return -1.0;   // just a photon, right?
  else if(type == I3Track::YAGLaser)
    return -1.0;
  else if(type >= I3Track::ZPrimary && type <=I3Track::ZPrimary+400)
    return -1.0;
  else if(type >= I3Track::APrimary && type <= I3Track::APrimary+400)
    return -1.0;
  else if(type == I3Track::Elph)
    // again, just an estimate until LHC starts running
    // 70 years = 70 * 365 * 24 * 60 * 60 seconds 
    return 2.2e9 * I3Units::s;

  return -1.0;
}

Bool_t I3ParticleDataService::Stable(I3Track::Type type)
{
  if(type ==I3Track::Null)
    return kFALSE;
  else if(type == I3Track::Unknown)
    return kFALSE;
  else if(type == I3Track::Gamma)
    return kTRUE;
  else if(type == I3Track::EPlus)
    return kTRUE;
  else if(type == I3Track::EMinus)
    return kTRUE;
  else if(type == I3Track::Nu)
    return kTRUE;
  else if(type == I3Track::MuPlus)
    return kFALSE;
  else if(type == I3Track::MuMinus)
    return kFALSE;
  else if(type == I3Track::Pi0)
    return kFALSE;
  else if(type == I3Track::PiPlus)
    return kFALSE;
  else if(type == I3Track::PiMinus)
    return kFALSE;
  else if(type == I3Track::PPlus)
    return kTRUE;
  else if(type == I3Track::PMinus)
    return kTRUE;
  else if(type == I3Track::TauPlus)
    return kFALSE;
  else if(type == I3Track::TauMinus)
    return kFALSE;
  else if(type == I3Track::NuE)
    return kTRUE;
  else if(type == I3Track::NuMu)
    return kTRUE;
  else if(type == I3Track::NuTau)
    return kTRUE;
  else if(type == I3Track::NuEBar)
    return kTRUE;
  else if(type == I3Track::NuMuBar)
    return kTRUE;
  else if(type == I3Track::Brems)
    return kTRUE;
  else if(type == I3Track::DeltaE)
    return kTRUE;
  else if(type == I3Track::PairProd)
    return kTRUE;
  else if(type == I3Track::NuclInt)
    return kTRUE;
  else if(type == I3Track::MuPair)
    return kTRUE;
  else if(type == I3Track::Hadrons)
    return kTRUE;
  else if(type == I3Track::FiberLaser)
    return kTRUE;
  else if(type == I3Track::N2Laser)
    return kTRUE;
  else if(type == I3Track::YAGLaser)
    return kTRUE;
  else if(type >= I3Track::ZPrimary && type <=I3Track::ZPrimary+400)
    return kTRUE;
  else if(type >= I3Track::APrimary && type <= I3Track::APrimary+400)
    return kTRUE;
  else if(type == I3Track::Elph)
    return kFALSE;
  return kTRUE;
}

Double_t I3ParticleDataService::Charge(I3Track::Type type)
{
  if(type ==I3Track::Null)
    return 0;
  else if(type == I3Track::Unknown)
    return 0;
  else if(type == I3Track::Gamma)
    return 0;
  else if(type == I3Track::EPlus)
    return 1 * I3Units::eplus;
  else if(type == I3Track::EMinus)
    return -1 * I3Units::eplus;
  else if(type == I3Track::Nu)
    return 0;
  else if(type == I3Track::MuPlus)
    return I3Units::eplus;
  else if(type == I3Track::MuMinus)
    return -1 * I3Units::eplus;
  else if(type == I3Track::Pi0)
    return 0;
  else if(type == I3Track::PiPlus)
    return I3Units::eplus;
  else if(type == I3Track::PiMinus)
    return -1 * I3Units::eplus;
  else if(type == I3Track::PPlus)
    return I3Units::eplus;
  else if(type == I3Track::PMinus)
    return -1 * I3Units::eplus;
  else if(type == I3Track::TauPlus)
    return I3Units::eplus;
  else if(type == I3Track::TauMinus)
    return -2 * I3Units::eplus;
  else if(type == I3Track::NuE)
    return 0;
  else if(type == I3Track::NuMu)
    return 0;
  else if(type == I3Track::NuTau)
    return 0;
  else if(type == I3Track::NuEBar)
    return 0;
  else if(type == I3Track::NuMuBar)
    return 0;
  else if(type == I3Track::Brems)
    return 0;
  else if(type == I3Track::DeltaE)
    return 0;
  else if(type == I3Track::PairProd)
    return 0;
  else if(type == I3Track::NuclInt)
    return 0;
  else if(type == I3Track::MuPair)
    return 0;
  else if(type == I3Track::Hadrons)
    return 0;
  else if(type == I3Track::FiberLaser)
    return 0;
  else if(type == I3Track::N2Laser)
    return 0;
  else if(type == I3Track::YAGLaser)
    return 0;
  else if(type >= I3Track::ZPrimary && type <=I3Track::ZPrimary+400)
    // is this right???
    return (type - I3Track::ZPrimary);
  else if(type >= I3Track::APrimary && type <= I3Track::APrimary+400)
    // just approximatin' here
    return (type - I3Track::APrimary)/2;
  else if(type == I3Track::Elph)
    return 0;
  return 0;

}

std::string I3ParticleDataService::ToString(I3Track::Type type)
{
  if(type ==I3Track::Null)
    return "Null";
  else if(type == I3Track::Unknown)
    return "Unknown";
  else if(type == I3Track::Gamma)
    return "Gamma";
  else if(type == I3Track::EPlus)
    return "Positron";
  else if(type == I3Track::EMinus)
    return "Electron";
  else if(type == I3Track::Nu)
    return "Neutrino";
  else if(type == I3Track::MuPlus)
    return "MuPlus";
  else if(type == I3Track::MuMinus)
    return "MuMinus";
  else if(type == I3Track::Pi0)
    return "Pi0";
  else if(type == I3Track::PiPlus)
    return "PiPlus";
  else if(type == I3Track::PiMinus)
    return "PiMinus";
  else if(type == I3Track::PPlus)
    return "Proton";
  else if(type == I3Track::PMinus)
    return "AntiProton";
  else if(type == I3Track::TauPlus)
    return "TauPlus";
  else if(type == I3Track::TauMinus)
    return "TauMinus";
  else if(type == I3Track::NuE)
    return "NuE";
  else if(type == I3Track::NuMu)
    return "NuMu";
  else if(type == I3Track::NuTau)
    return "NuTau";
  else if(type == I3Track::NuEBar)
    return "NuEBar";
  else if(type == I3Track::NuMuBar)
    return "NuMuBar";
  else if(type == I3Track::Brems)
    return "Brems";
  else if(type == I3Track::DeltaE)
    return "DeltaE";
  else if(type == I3Track::PairProd)
    return "PairProd";
  else if(type == I3Track::NuclInt)
    return "NuclInt";
  else if(type == I3Track::MuPair)
    return "MuPair";
  else if(type == I3Track::Hadrons)
    return "Hadrons";
  else if(type == I3Track::FiberLaser)
    return "FiberLaser";
  else if(type == I3Track::N2Laser)
    return "N2Laser";
  else if(type == I3Track::YAGLaser)
    return "YAGLaser";
  else if(type >= I3Track::ZPrimary && type <=I3Track::ZPrimary+400)
    {
      char output[255];
      sprintf(output,"ZPrimary_%d",type-I3Track::ZPrimary);
      std::string to_return(output);
      return to_return;
    }
  else if(type >= I3Track::APrimary && type <= I3Track::APrimary+400)
    {
      char output[255];
      sprintf(output,"APrimary_%d",type-I3Track::APrimary);
      std::string to_return(output);
      return to_return;
    }
  else if(type == I3Track::Elph)
    return "Elephantino";

  return "Unknown";
}

const Char_t* I3ParticleDataService::DefaultName()
{
  return "ParticleData";
}
