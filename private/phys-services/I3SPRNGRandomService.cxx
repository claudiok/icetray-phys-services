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

I3SPRNGRandomService::I3SPRNGRandomService(int seed, int nstreams, int streamnum)
{
  gsl_rng_env_setup();
  r = gsl_sprng_init(seed, nstreams, streamnum);
}

I3SPRNGRandomService::~I3SPRNGRandomService()
{
   gsl_sprng_free(r);
}

int I3SPRNGRandomService::Binomial(int ntot, double prob)
{
  return gsl_ran_binomial(r,prob,ntot);
}

double I3SPRNGRandomService::Exp(double tau)
{
  return gsl_ran_exponential(r,tau);
}

unsigned int I3SPRNGRandomService::Integer(unsigned int imax)
{
  return (unsigned int)Uniform(imax);
}

int I3SPRNGRandomService::Poisson(double mean)
{
  return gsl_ran_poisson(r,mean);
}

double I3SPRNGRandomService::PoissonD(double mean)
{
  return gsl_ran_poisson(r,mean);
}

double I3SPRNGRandomService::Uniform(double x1)
{
  return gsl_ran_flat(r,0.0,x1);
}

double I3SPRNGRandomService::Uniform(double x1, double x2)
{
  return gsl_ran_flat(r,x1,x2);
}

double I3SPRNGRandomService::Gaus(double mean,double stddev)
{
  return mean + gsl_ran_gaussian(r,stddev);
}
