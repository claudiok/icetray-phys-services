/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3RandomService.h,v 1.7 2004/10/20 12:12:15 pretz Exp $
 *
 *
 * This class is just the interface.  The names chosen
 * reflect ROOT's TRandom interface.  Indeed TRandom could be used to 
 * trivially fill this interface
 *
 * @version $Revision: 1.7 $
 * @date $Date: 2004/10/20 12:12:15 $
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
  virtual Int_t Binomial(Int_t ntot, Double_t prob)=0;

  // Apparently, my version of ROOT doesn't have this, so I left it out.
  /* virtual Double_t BreitWigner(Double_t mean = 0, Double_t gamma = 1)=0; */
  
  /**
   * A number from an Exponential distribution
   */
  virtual Double_t Exp(Double_t tau)=0;

  /**
   * An integer drawn uniformly from [0,imax)
   */
  virtual UInt_t Integer(UInt_t imax)=0;

  /**
   * An integer drawn from a Poisson distribution
   */
  virtual Int_t Poisson(Double_t mean)=0;

  /**
   * A number drawn from a Poisson distribution, as a double
   */
  virtual Double_t PoissonD(Double_t mean)=0;

  /**
   * a Double_t drawn from a uniform distribution (0,x1)
   */
  virtual Double_t Uniform(Double_t x1 = 1)=0;

  /**
   * a Double_t drawn from a uniform distribution (x1,x2)
   */
  virtual Double_t Uniform(Double_t x1, Double_t x2)=0;

  /**
   * gives a default name for this service
   */
  static const Char_t* DefaultName(){return "RandomService";}

 private:
  // copy and assignment private
  I3RandomService(const I3RandomService&);
  const I3RandomService& operator=(const I3RandomService&);

  //ROOT macro
  ClassDef(I3RandomService,0);
};

typedef PtrPolicy<I3RandomService>::ThePolicy I3RandomServicePtr;

#endif //I3RANDOMSERVICE_H
