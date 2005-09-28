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
 
// class header file

#include "phys-services/I3MediumServiceFactory.h"

#include "icetray/I3ServicesAccess.h"
#include "phys-services/I3MediumPropertiesFile.h"

// namespace declarations



// implementation

I3MediumServiceFactory::I3MediumServiceFactory(const I3Context& context)
  : I3ServiceFactory(context),
  	medium_(){
  	
  AddParameter("Properties", "Ice properties file (input)",
  	mediumPropInFilename_);
  AddParameter("Histograms", "ROOT file to dump lookup tables into (output)",
  	mediumHistoOutFilename_);
}


I3MediumServiceFactory::~I3MediumServiceFactory(){
}


bool I3MediumServiceFactory::InstallService(I3Services& services){
	
  if(!medium_){
  	if(!mediumPropInFilename_.empty()){
			I3MediumPropertiesFile properties(mediumPropInFilename_);
			medium_ = I3MediumServicePtr(new I3MediumService(properties,
				mediumHistoOutFilename_));
		}
		else medium_ = I3MediumServicePtr(new I3MediumService);
	}

  return I3ServicesAccess<I3MediumService>::Put(services, medium_,
  	I3MediumService::DefaultName());
}


void I3MediumServiceFactory::Configure(){
	
  GetParameter("Properties", mediumPropInFilename_);
  GetParameter("Histograms", mediumHistoOutFilename_);
}
