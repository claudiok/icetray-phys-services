#ifndef I3TRANDOMSERVICE_H
#define I3TRANDOMSERVICE_H

#include "phys-services/I3RandomService.h"
#include "TRandom.h"

/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3TRandomService.h,v 1.3 2004/05/10 15:57:54 pretz Exp $
 *
 * @brief An implementation of the I3RandomService interface.  
 * 
 * Just uses
 * a private TRandom to implement the methods of I3RandomService.
 *
 * @version $Revision: 1.3 $
 * @date $Date: 2004/05/10 15:57:54 $
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
  I3TRandomService(UInt_t seed) : fRand(seed){}

  /**
   * destructor
   */
  virtual ~I3TRandomService(){};

  /**
   * a number drawn from a binomial distribution
   */
  virtual Int_t Binomial(Int_t ntot, Double_t prob);

  // Apparently, my version of ROOT doesn't have this, so I left it out.
  /* virtual Double_t BreitWigner(Double_t mean = 0, Double_t gamma = 1)=0; */
  
  /**
   * A number from an Exponential distribution
   */
  virtual Double_t Exp(Double_t tau);

  /**
   * An integer drawn uniformly from [0,imax)
   */
  virtual UInt_t Integer(UInt_t imax);

  /**
   * a number drawn from a Landau distribution
   */
  virtual Double_t Landau(Double_t mean = 0, Double_t sigma = 1);

  /**
   * An integer drawn from a Poisson distribution
   */
  virtual Int_t Poisson(Double_t mean);

  /**
   * A number drawn from a Poisson distribution, as a double
   */
  virtual Double_t PoissonD(Double_t mean);

  /**
   * Uniform Double_t on the interval (0,1).  You got me what that integer
   * is for.  Near as I can figure it's useless, and the ROOT doc's don't say
   */
  virtual Double_t Rndm(Int_t i = 0);

  /**
   * a Double_t drawn from a uniform distribution (0,x1)
   */
  virtual Double_t Uniform(Double_t x1 = 1);

  /**
   * a Double_t drawn from a uniform distribution (x1,x2)
   */
  virtual Double_t Uniform(Double_t x1, Double_t x2);
 private:
  TRandom fRand;

  ClassDef(I3TRandomService,0);
};


#endif //I3TRANDOMSERVICE_H
