#include "phys-services/I3GSLRandomService.h"

ClassImp(I3GSLRandomService);

I3GSLRandomService::I3GSLRandomService()
{
  construct();
}

I3GSLRandomService::I3GSLRandomService(unsigned long int seed)
{
  construct();
  gsl_rng_set(r, seed);
}

int I3GSLRandomService::Binomial(int ntot, double prob)
{
  return gsl_ran_binomial(r,prob,ntot);
}

double I3GSLRandomService::Exp(double tau)
{
  return gsl_ran_exponential(r,tau);
}

unsigned int I3GSLRandomService::Integer(unsigned int imax)
{
  return (unsigned int)Uniform(imax);
}

int I3GSLRandomService::Poisson(double mean)
{
  return gsl_ran_poisson(r,mean);
}

double I3GSLRandomService::PoissonD(double mean)
{
  return gsl_ran_poisson(r,mean);
}

double I3GSLRandomService::Uniform(double x1)
{
  return gsl_ran_flat(r,0.0,x1);
}

double I3GSLRandomService::Uniform(double x1, double x2)
{
  return gsl_ran_flat(r,x1,x2);
}

double I3GSLRandomService::Gaus(double mean,double stddev)
{
  return mean + gsl_ran_gaussian(r,stddev);
}
