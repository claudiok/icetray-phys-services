#include "phys-services/I3GSLRandomService.h"

ClassImp(I3GSLRandomService);

I3GSLRandomService::I3GSLRandomService()
{
  gsl_rng_env_setup();
  r = gsl_rng_alloc(gsl_rng_default);
}

Int_t I3GSLRandomService::Binomial(Int_t ntot, Double_t prob)
{
  return gsl_ran_binomial(r,prob,ntot);
}

Double_t I3GSLRandomService::Exp(Double_t tau)
{
  return gsl_ran_exponential(r,tau);
}

UInt_t I3GSLRandomService::Integer(UInt_t imax)
{
  return (UInt_t)Uniform(imax);
}

Int_t I3GSLRandomService::Poisson(Double_t mean)
{
  return gsl_ran_poisson(r,mean);
}

Double_t I3GSLRandomService::PoissonD(Double_t mean)
{
  return gsl_ran_poisson(r,mean);
}

Double_t I3GSLRandomService::Uniform(Double_t x1)
{
  return gsl_ran_flat(r,0.0,x1);
}

Double_t I3GSLRandomService::Uniform(Double_t x1, Double_t x2)
{
  return gsl_ran_flat(r,x1,x2);
}
