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
 * @version $Revision: 1.10 $
 * @date $Date$
 * @author pretz
 *
 * @todo 
 */

#ifndef I3RANDOMSERVICE_H
#define I3RANDOMSERVICE_H

#include "Rtypes.h"
#include "dataclasses/StoragePolicy.h"

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

  // Apparently, my version of ROOT doesn't have this, so I left it out.
  /* virtual double BreitWigner(double mean = 0, double gamma = 1)=0; */
  
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

  /**
   * gives a default name for this service
   */
  static const char* DefaultName(){ return "RandomService"; }

 private:
  // copy and assignment private
  I3RandomService(const I3RandomService&);
  const I3RandomService& operator=(const I3RandomService&);

  //ROOT macro
  ClassDef(I3RandomService,0);
};

typedef shared_ptr<I3RandomService> I3RandomServicePtr;

#endif //I3RANDOMSERVICE_H
