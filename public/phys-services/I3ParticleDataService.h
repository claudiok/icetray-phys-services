#ifndef I3PARTICLESDATAERVICE_H
#define I3PARTICLESDATAERVICE_H

#include "dataclasses/I3Track.h"
#include "Rtypes.h"
#include <string>


class I3ParticleDataService {
 public:
  I3ParticleDataService();
  virtual ~I3ParticleDataService();

  virtual I3Track::Type TranslateFromF2k(Int_t f2k_id);
  virtual I3Track::Type TranslateFromString(const Char_t* name);
  virtual I3Track::Type TranslateFromPDG(Int_t pdg_id);
  virtual I3Track::Type TranslateFromCorsika(Int_t corsika_id);
  virtual Double_t Mass(I3Track::Type particle);
  virtual Double_t LifeTime(I3Track::Type particle);
  virtual Bool_t Stable(I3Track::Type particle);
  virtual Double_t Charge(I3Track::Type particle);
  std::string ToString(I3Track::Type);

  static const Char_t* DefaultName();

 private:
  ClassDef(I3ParticleDataService,0);

};

#endif //I3PARTICLESDATAERVICE_H
