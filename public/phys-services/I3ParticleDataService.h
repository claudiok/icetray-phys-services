#ifndef I3PARTICLESDATAERVICE_H
#define I3PARTICLESDATAERVICE_H

#include "dataclasses/I3Track.h"
#include "Rtypes.h"
#include <string>
/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3ParticleDataService.h,v 1.5 2004/04/22 16:16:26 pretz Exp $
 *
 * This class provides frequently needed operations on the Particle types.
 * Stuff like convering them between systems, and finding physical 
 * parameters of them.  Note that the physical parameters uses the I3Units
 * conventions, so to get a lifetime in ns for instance you'd do
 * Lifetime(I3Track::MuMinus)/I3Units::ns
 *
 * @version $Revision: 1.5 $
 * @date $Date: 2004/04/22 16:16:26 $
 * @author pretz
 *
 * @todo implment the TranslateFromPDG and TranslateFromCorsika methods
 */
class I3ParticleDataService {
 public:
  /**
   * constructor
   */
  I3ParticleDataService();

  /**
   * destructor
   */
  virtual ~I3ParticleDataService();

  /**
   * translates a particle type from the f2k convention
   * @param f2k_id a particle id in the f2k convention
   * @return the corresponding I3Track::Type in the dataclasses convention
   */
  virtual I3Particle::ParticleType TranslateFromF2k(Int_t f2k_id);

  /**
   * translates a particle from a character string.
   * @todo Is this needed?  I don't think so.  Remove this
   */
  virtual I3Particle::ParticleType TranslateFromString(const Char_t* name);

  /**
   * Translates a particle type from the PDG convention
   * @param pdg_id the particle type in the PDG convention
   * @return the corresponding TrackType in the datacalsses convention
   * @todo implement this method
   */
  virtual I3Particle::ParticleType TranslateFromPDG(Int_t pdg_id);

  /**
   * Translates a particle type from the Corsika convention
   * @param pdg_id the particle type in the Corsika convention
   * @return the corresponding I3Particle::ParticleType in the datacalsses convention
   * @todo implement this message.
   */
  virtual I3Particle::ParticleType TranslateFromCorsika(Int_t corsika_id);

  /**
   * Retrieves the mass of a particle in units of Energy.
   * @param particle the particle you want to know the mass of
   * @return the mass of the particle as an energy
   */
  virtual Double_t Mass(I3Particle::ParticleType particle);

  /**
   * Gets the lifetime of a particle
   * @param particle the particle you want to know the lifetime of
   * @return the lifetime of the particle.  Gives -1 if its stable.
   */
  virtual Double_t LifeTime(I3Particle::ParticleType particle);

  /**
   * identifies a particle as stable.
   * @param particle the particle you want to know about
   * @return kTRUE if the particle is stable
   */
  virtual Bool_t Stable(I3Particle::ParticleType particle);

  /**
   * gives the charge of particles in the units of I3Units
   * @param particle the particle you want to know about
   * @return the charge of that particle
   */
  virtual Double_t Charge(I3Particle::ParticleType particle);

  /**
   * generates a string name for the indicated particle type.
   * Useful for 'printing' or soething like that.  Example output would be
   * "Positron".  
   * @param particle the particle you want to convert to a string
   * @return a string identifying that particle
   */
  std::string ToString(I3Particle::ParticleType particle);

  /**
   * Gives the 'photonics id' of the particle type.  
   * '0' for muons, '1' for em-showers, '2' for hadronic showers
   * '-1' if its unknown
   */
  Int_t LightType(I3Particle::ParticleType particle);

  /**
   * a default name for the service.  
   * @return the default name for the service
   */
  static const Char_t* DefaultName();

 private:
  // copy and assignment are private
  I3ParticleDataService(const I3ParticleDataService&);
  const I3ParticleDataService& operator=(const I3ParticleDataService&);

  //ROOT macro
  ClassDef(I3ParticleDataService,0);

};

#endif //I3PARTICLESDATAERVICE_H
