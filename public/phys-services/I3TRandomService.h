#ifndef I3TRANDOMSERVICE_H
#define I3TRANDOMSERVICE_H

#include "phys-services/I3RandomService.h"
#include "TRandom.h"

/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3TRandomService.h,v 1.6 2005/04/04 18:40:40 pretz Exp $
 *
 * @brief An implementation of the I3RandomService interface.  
 * 
 * Just uses
 * a private TRandom to implement the methods of I3RandomService.
 *
 * @version $Revision: 1.6 $
 * @date $Date: 2005/04/04 18:40:40 $
 * @author pretz
 *
 * @todo 
 */
class I3TRandomService : public I3RandomService{
 public:
  /**
   * default constructor
   * Builds the private TRandom in the default way.
   */
  I3TRandomService(){};

  /**
   * constructor
   * Builds the private TRandom with the indicated seed
   * @param seed the seed value you want for the TRandom
   */
  I3TRandomService(unsigned int seed) : fRand(seed){}

  /**
   * destructor
   */
  virtual ~I3TRandomService(){};

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
  TRandom fRand;

  ClassDef(I3TRandomService,0);
};


#endif //I3TRANDOMSERVICE_H
