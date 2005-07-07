/**
 * Implementation of I3MediumServiceFactory class
 *
 * (c) 2005
 * the IceCube Collaboration
 * $Id:  $
 *
 * @file I3MediumServiceFactory.cxx
 * @version $Revision:  $
 * @date $Date:  $
 * @author tschmidt
 */
 
// Class header file

#include "phys-services/I3MediumServiceFactory.h"

ClassImp(I3MediumServiceFactory);

// Other header files

#include "icetray/I3ServicesAccess.h"

// Implementation

I3MediumServiceFactory::I3MediumServiceFactory(const I3Context& context)
  : I3ServiceFactory(context),
  	medium_(){
  	
  AddParameter("Properties", "Amanda ice properties file (input)",
  	mediumPropInFilename_);
  AddParameter("Histograms", "ROOT file to dump lookup tables into (output)",
  	mediumHistoOutFilename_);
}


I3MediumServiceFactory::~I3MediumServiceFactory(){
}


bool I3MediumServiceFactory::InstallService(I3Services& services){
	
  if(!medium_){
		medium_ = I3MediumServicePtr(new I3MediumService());
		if(!(mediumPropInFilename_.empty()))
			medium_->Initialize( mediumPropInFilename_, mediumHistoOutFilename_ );
	}

  return I3ServicesAccess<I3MediumService>::Put(services, medium_,
  	I3MediumService::DefaultName());
}


void I3MediumServiceFactory::Configure(){
	
  GetParameter("Properties", mediumPropInFilename_);
  GetParameter("Histograms", mediumHistoOutFilename_);
  
  if(medium_ && !(mediumPropInFilename_.empty()))
  	medium_->Initialize( mediumPropInFilename_, mediumHistoOutFilename_ );
}
