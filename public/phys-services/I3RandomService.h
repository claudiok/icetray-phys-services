/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id$
 *
 *
 * This class is just the interface.  The names chosen
 * reflect ROOT's TRandom interface.  Indeed TRandom could be used to 
 * trivially fill this interface
 *
 * @version $Revision$
 * @date $Date$
 * @author pretz
 *
 * @todo 
 */

#ifndef I3RANDOMSERVICE_H
#define I3RANDOMSERVICE_H

#include "dataclasses/Utility.h"
#include <icetray/I3DefaultName.h>
#include <icetray/I3FrameObject.h>

struct gsl_rng_wrap;

/**
 * @brief This class provides an interface to random numbers suitable for use
 * by icetray modules.
 *
 * This class is just the interface.  The names chosen
 * reflect ROOT's TRandom interface.  Indeed TRandom could be used to 
 * trivially fill this interface
 *
 * Only one function here is required: Uniform(x1, x2)
 * The rest have default implementations in terms of it. More complicated
 * random number distributions than provided here can be obtained using
 * the GSL bridge (GSLRng()).
 * 
 * NOTE: when using the GSL bridge, this file MUST be included AFTER
 * gsl/gsl_rng.h
 *
 */

class I3RandomService {
 public:
  /**
   * constructor
   */
  I3RandomService();

  /**
   * destructor
   */ 
  virtual ~I3RandomService();

  /**
   * a number drawn from a binomial distribution
   */
  virtual int Binomial(int ntot, double prob);

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
  virtual double Uniform(double x1, double x2)=0;

  /**
   * a double drawn from a Gaussian distribution with given
   * mean and standard deviation
   */
  virtual double Gaus(double mean,double stddev);
   
  /**
   * get all information necessary to restore the internal
   * state of the generator
   */
  virtual I3FrameObjectPtr GetState() const
  {
  	log_fatal("This generator cannot save state.");
  	return I3FrameObjectPtr();
  }
   
  /**
   * restore the internal state of the generator
   */
  virtual void RestoreState(I3FrameObjectConstPtr state)
  {
  	log_fatal("This generator cannot restore state.");
  }

  /**
   * a gsl_rng that wraps this random service, for use with
   * GSL random samplers and C APIs
   */
  const gsl_rng_wrap *GSLRng() const;

 private:
  // copy and assignment private
  I3RandomService(const I3RandomService&);
  const I3RandomService& operator=(const I3RandomService&);

  gsl_rng_wrap *gsl_;

  SET_LOGGER("I3RandomService");

};

I3_DEFAULT_NAME(I3RandomService);
I3_POINTER_TYPEDEFS(I3RandomService);

#endif //I3RANDOMSERVICE_H

#if defined(__GSL_RNG_H__) && !defined(I3_GSL_RNG_WRAP)
#define I3_GSL_RNG_WRAP
struct gsl_rng_wrap : public gsl_rng {};
#endif

