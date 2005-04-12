#ifndef I3GSLRANDOMSERVICE_H
#define I3GSLRANDOMSERVICE_H

#include "phys-services/I3RandomService.h"

#include <gsl/gsl_randist.h>
#include <gsl/gsl_rng.h>
#include <gsl/gsl_test.h>

/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3GSLRandomService.h,v 1.5 2005/04/12 18:43:58 pretz Exp $
 *
 * @brief An implementation of the I3RandomService interface.  
 * 
 * Uses the gsl library for the random numbers
 *
 * @version $Revision: 1.5 $
 * @date $Date: 2005/04/12 18:43:58 $
 * @author pretz
 *
 * @todo 
 */
class I3GSLRandomService : public I3RandomService{
 public:
  /**
   * default constructor
   */
  I3GSLRandomService();

  /**
   * destructor
   */
  virtual ~I3GSLRandomService(){};

  /**
   * a number drawn from a binomial distribution
   */
  virtual int Binomial(int ntot, double prob);

  // Apparently, my version of ROOT doesn't have this, so I left it out.
  /* virtual double BreitWigner(double mean = 0, double gamma = 1)=0; */
  
  /**
   * A number from an Exponential distribution
   */
  virtual double Exp(double tau);

  /**
   * An integer drawn uniformly from [0,imax)
   */
  virtual unsigned int Integer(unsigned int imax);

  /**
   * An integer drawn from a Poisson distribution
   */
  virtual int Poisson(double mean);

  /**
   * A number drawn from a Poisson distribution, as a double
   */
  virtual double PoissonD(double mean);

  /**
   * a double drawn from a uniform distribution (0,x1)
   */
  virtual double Uniform(double x1 = 1);

  /**
   * a double drawn from a uniform distribution (x1,x2)
   */
  virtual double Uniform(double x1, double x2);

  /**
   * a double drawn from a Gaussian distribution with given
   * mean and standard deviation
   */
  virtual double Gaus(double mean, double stddev);

 private:

  gsl_rng* r;

  ClassDef(I3GSLRandomService,0);
};

typedef shared_ptr<I3GSLRandomService> I3GSLRandomServicePtr;

#endif //I3GSLRANDOMSERVICE_H
