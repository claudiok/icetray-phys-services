/**
 * copyright  (C) 2004
 * the icecube collaboration
 * $Id: I3StdServiceModule.h,v 1.1 2004/07/16 19:24:51 pretz Exp $
 *
 * @file I3StdServiceModule.h
 * @version $Revision: 1.1 $
 * @date $Date: 2004/07/16 19:24:51 $
 * @author pretz
 */
#include "icetray/I3Module.h"
#include "icetray/I3ContextAccess.h"
#include "I3ParticleDataService.h"
#include "I3Calculator.h"
#include "I3RandomService.h"

/**
 * A class which provides helper methods to access standard services.
 * If a module inherits from this class, it doesn't have to go through
 * the cumbersome I3ContextAccess<>::GetService() syntax
 *
 * @author pretz
 * 
 */
class I3StdServiceModule : public I3Module
{
 public:
  I3StdServiceModule(I3Context& ctx) : I3Module(ctx){}
  virtual ~I3StdServiceModule(){}

  I3ParticleDataService& GetParticleData(const string& name)
    {
      return I3ContextAccess<I3ParticleDataService>::
	GetService(GetContext(),name);
    }

  I3Calculator& GetCalculator(const string& name)
    {
      return I3ContextAccess<I3Calculator>::
	GetService(GetContext(),name);
    }
  I3RandomService& GetRandom(const string& name)
    {
      return I3ContextAccess<I3RandomService>::
	GetService(GetContext(),name);
    }
  ClassDef(I3StdServiceModule,0);
};
