#include "phys-services/I3TRandomService.h"

ClassImp(I3TRandomService);

int I3TRandomService::Binomial(int ntot, double prob)
{
  return fRand.Binomial(ntot,prob);
}

// double I3TRandomService::BreitWigner(double mean, double gamma)
// {
//   return fRand.BreitWigner(mean,gamma);
// }

double I3TRandomService::Exp(double tau)
{
  return fRand.Exp(tau);
}

unsigned int I3TRandomService::Integer(unsigned int imax)
{
  return fRand.Integer(imax);
}

int I3TRandomService::Poisson(double mean)
{
  return fRand.Poisson(mean);
}

double I3TRandomService::PoissonD(double mean)
{
  return fRand.PoissonD(mean);
}

double I3TRandomService::Uniform(double x1)
{
  return fRand.Uniform(x1);
}

double I3TRandomService::Uniform(double x1, double x2)
{
  return fRand.Uniform(x1,x2);
}

double I3TRandomService::Gaus(double mean,double stddev)
{
  return fRand.Gaus(mean,stddev);
}
