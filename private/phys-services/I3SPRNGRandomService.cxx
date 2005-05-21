/*
 * class: I3SPRNGRandomService
 *
 * Version $Id$
 *
 * Date: 2 Apr 2005
 *
 * (c) IceCube Collaboration
 */

// Class header files
#include "phys-services/I3SPRNGRandomService.h"
#include "phys-services/gsl-sprng.h" 

ClassImp(I3SPRNGRandomService);

I3SPRNGRandomService::I3SPRNGRandomService()
{
  gsl_rng_env_setup();
  r = gsl_sprng_init(0, 1, 0);
}

I3SPRNGRandomService::I3SPRNGRandomService(Int_t seed, Int_t nstreams, Int_t streamnum)
{
  gsl_rng_env_setup();
  r = gsl_sprng_init(seed, nstreams, streamnum);
}

I3SPRNGRandomService::~I3SPRNGRandomService()
{
   gsl_sprng_free(r);
}

Int_t I3SPRNGRandomService::Binomial(Int_t ntot, Double_t prob)
{
  return gsl_ran_binomial(r,prob,ntot);
}

Double_t I3SPRNGRandomService::Exp(Double_t tau)
{
  return gsl_ran_exponential(r,tau);
}

UInt_t I3SPRNGRandomService::Integer(UInt_t imax)
{
  return (UInt_t)Uniform(imax);
}

Int_t I3SPRNGRandomService::Poisson(Double_t mean)
{
  return gsl_ran_poisson(r,mean);
}

Double_t I3SPRNGRandomService::PoissonD(Double_t mean)
{
  return gsl_ran_poisson(r,mean);
}

Double_t I3SPRNGRandomService::Uniform(Double_t x1)
{
  return gsl_ran_flat(r,0.0,x1);
}

Double_t I3SPRNGRandomService::Uniform(Double_t x1, Double_t x2)
{
  return gsl_ran_flat(r,x1,x2);
}

Double_t I3SPRNGRandomService::Gaus(Double_t mean,Double_t stddev)
{
  return mean + gsl_ran_gaussian(r,stddev);
}
