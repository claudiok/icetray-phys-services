#ifndef I3TRANDOMSERVICE_H
#define I3TRANDOMSERVICE_H

#include "phys-services/I3RandomService.h"
#include "TRandom.h"

class I3TRandomService : public I3RandomService{
 public:
  I3TRandomService(){};
  virtual ~I3TRandomService(){};
  virtual Int_t Binomial(Int_t ntot, Double_t prob);
/*   virtual Double_t BreitWigner(Double_t mean = 0, Double_t gamma = 1); */
  virtual Double_t Exp(Double_t tau);
  virtual UInt_t Integer(UInt_t imax);
  virtual Double_t Landau(Double_t mean = 0, Double_t sigma = 1);
  virtual Int_t Poisson(Double_t mean);
  virtual Double_t PoissonD(Double_t mean);
  virtual Double_t Rndm(Int_t i = 0);
  virtual Double_t Uniform(Double_t x1 = 1);
  virtual Double_t Uniform(Double_t x1, Double_t x2);
 private:
  TRandom fRand;

  ClassDef(I3TRandomService,0);
};


#endif //I3TRANDOMSERVICE_H
