#ifndef I3RANDOMSERVICE_H
#define I3RANDOMSERVICE_H

#include "Rtypes.h"

class I3RandomService {
 public:
  virtual ~I3RandomService(){};
  virtual Int_t Binomial(Int_t ntot, Double_t prob)=0;
/*   virtual Double_t BreitWigner(Double_t mean = 0, Double_t gamma = 1)=0; */
  virtual Double_t Exp(Double_t tau)=0;
  virtual UInt_t Integer(UInt_t imax)=0;
  virtual Double_t Landau(Double_t mean = 0, Double_t sigma = 1)=0;
  virtual Int_t Poisson(Double_t mean)=0;
  virtual Double_t PoissonD(Double_t mean)=0;
  virtual Double_t Rndm(Int_t i = 0)=0;
  virtual Double_t Uniform(Double_t x1 = 1)=0;
  virtual Double_t Uniform(Double_t x1, Double_t x2)=0;
  static const Char_t* DefaultName(){return "RandomService";}
  ClassDef(I3RandomService,0);
};


#endif //I3RANDOMSERVICE_H
