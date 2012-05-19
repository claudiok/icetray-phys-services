#ifndef I3GSLRANDOMSERVICE_H
#define I3GSLRANDOMSERVICE_H

#include "phys-services/I3RandomService.h"

struct i3_gsl_rng;

/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 * @brief An implementation of the I3RandomService interface.  
 * 
 * Uses the gsl library for the random numbers
 *
 * @version $Revision: 1.5 $
 * @date $Date$
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
   * constructor
   */
	I3GSLRandomService(unsigned long int seed);

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

  // private copy constructors and assignment
  I3GSLRandomService(const I3GSLRandomService& );
  I3GSLRandomService operator=(const I3GSLRandomService& );

  i3_gsl_rng* r;

  SET_LOGGER("I3GSLRandomService");

};

I3_POINTER_TYPEDEFS(I3GSLRandomService);

#endif //I3GSLRANDOMSERVICE_H
