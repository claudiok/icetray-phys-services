/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3RandomService.h 35911 2007-08-23 05:12:17Z troy $
 *
 *
 * This class is just the interface.  The names chosen
 * reflect ROOT's TRandom interface.  Indeed TRandom could be used to 
 * trivially fill this interface
 *
 * @version $Revision: 1.10 $
 * @date $Date: 2007-08-23 00:12:17 -0500 (Thu, 23 Aug 2007) $
 * @author pretz
 *
 * @todo 
 */

#ifndef I3RANDOMSERVICE_H
#define I3RANDOMSERVICE_H

#include "dataclasses/Utility.h"
#include <icetray/I3DefaultName.h>
#include <icetray/I3FrameObject.h>

/**
 * @brief This class provides an interface to random numbers suitable for use
 * by icetray modules.
 *
 * This class is just the interface.  The names chosen
 * reflect ROOT's TRandom interface.  Indeed TRandom could be used to 
 * trivially fill this interface
 *
 */

class I3RandomService {
 public:
  /**
   * constructor
   */
  I3RandomService(){}

  /**
   * destructor
   */ 
  virtual ~I3RandomService(){};

  /**
   * a number drawn from a binomial distribution
   */
  virtual int Binomial(int ntot, double prob)=0;

  /**
   * A number from an Exponential distribution
   */
  virtual double Exp(double tau)=0;

  /**
   * An integer drawn uniformly from [0,imax)
   */
  virtual unsigned int Integer(unsigned int imax)=0;

  /**
   * An integer drawn from a Poisson distribution
   */
  virtual int Poisson(double mean)=0;

  /**
   * A number drawn from a Poisson distribution, as a double
   */
  virtual double PoissonD(double mean)=0;

  /**
   * a double drawn from a uniform distribution (0,x1)
   */
  virtual double Uniform(double x1 = 1)=0;

  /**
   * a double drawn from a uniform distribution (x1,x2)
   */
  virtual double Uniform(double x1, double x2)=0;

  /**
   * a double drawn from a Gaussian distribution with given
   * mean and standard deviation
   */
  virtual double Gaus(double mean,double stddev) = 0;

 private:
  // copy and assignment private
  I3RandomService(const I3RandomService&);
  const I3RandomService& operator=(const I3RandomService&);

  SET_LOGGER("I3RandomService");

};

I3_DEFAULT_NAME(I3RandomService);
I3_POINTER_TYPEDEFS(I3RandomService);

#endif //I3RANDOMSERVICE_H
