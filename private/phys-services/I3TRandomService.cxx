#include "phys-services/I3TRandomService.h"

//ClassImp(I3TRandomService);

Int_t I3TRandomService::Binomial(Int_t ntot, Double_t prob)
{
  return fRand.Binomial(ntot,prob);
}

// Double_t I3TRandomService::BreitWigner(Double_t mean, Double_t gamma)
// {
//   return fRand.BreitWigner(mean,gamma);
// }

Double_t I3TRandomService::Exp(Double_t tau)
{
  return fRand.Exp(tau);
}

UInt_t I3TRandomService::Integer(UInt_t imax)
{
  return fRand.Integer(imax);
}

Int_t I3TRandomService::Poisson(Double_t mean)
{
  return fRand.Poisson(mean);
}

Double_t I3TRandomService::PoissonD(Double_t mean)
{
  return fRand.PoissonD(mean);
}

Double_t I3TRandomService::Uniform(Double_t x1)
{
  return fRand.Uniform(x1);
}

Double_t I3TRandomService::Uniform(Double_t x1, Double_t x2)
{
  return fRand.Uniform(x1,x2);
}

Double_t I3TRandomService::Gaus(Double_t mean,Double_t stddev)
{
  return fRand.Gaus(mean,stddev);
}
