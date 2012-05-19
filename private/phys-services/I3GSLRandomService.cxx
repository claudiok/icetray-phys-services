#include "phys-services/I3GSLRandomService.h"

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_test.h>
struct i3_gsl_rng : public gsl_rng{};

I3GSLRandomService::I3GSLRandomService()
{
  // needed call to gsl
  gsl_rng_env_setup();
  r = static_cast<i3_gsl_rng*>(gsl_rng_alloc(gsl_rng_default));
}

I3GSLRandomService::I3GSLRandomService(unsigned long int seed)
{
  // needed call to gsl.  Then set the seed.
  gsl_rng_env_setup();
  r = static_cast<i3_gsl_rng*>(gsl_rng_alloc(gsl_rng_default));
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
