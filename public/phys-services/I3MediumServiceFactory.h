/**
 * Definition of I3MediumServiceFactory class
 *
 * (c) 2005
 * the IceCube Collaboration
 * $Id:  $
 *
 * @file I3MediumServiceFactory.h
 * @version $Revision:  $
 * @date $Date:  $
 * @author tschmidt
 */
 
#ifndef I3_MEDIUM_SERVICE_FACTORY_H_INCLUDED
#define I3_MEDIUM_SERVICE_FACTORY_H_INCLUDED

// forward declarations

class I3Context;
class I3Services;

// header files

#include <string>
#include "icetray/I3ServiceFactory.h"
#include "phys-services/I3MediumService.h"
#include "services/I3Logging.h"

// definitions


/**
 * @brief This class installs an I3MediumService.
 * 
 * I3MediumService supports two parameters:
 * <VAR>Properties</VAR> and <VAR>Histograms</VAR>.
 * <VAR>Properties</VAR> defines an ice properties file,
 * <VAR>Histograms</VAR> defines a ROOT file into which lookup tables
 * might be dumped. <VAR>Histograms</VAR> makes an impact, only if
 * <VAR>Properties</VAR> is set and not empty.
 */
class I3MediumServiceFactory : public I3ServiceFactory{
 	
	public:

	/**
	 * @brief Constructor.
   * 
   * @param context the context in which the service will exist.
   */
	explicit I3MediumServiceFactory(const I3Context& context);

  /**
   * @brief Destructor.
   */
  virtual ~I3MediumServiceFactory();

  /**
   * @brief Installs this objects service into the specified services object.
   *
   * @param services The services object into which the service should be installed.
   * @return True, if the service is successfully installed.
   */
  virtual bool InstallService(I3Services& services);

  /**
   * @brief Configure service prior to installing it. 
   */
  virtual void Configure();

 private:

  // private copy constructors and assignment
  I3MediumServiceFactory(const I3MediumServiceFactory& );
  I3MediumServiceFactory operator=(const I3MediumServiceFactory& );

  // instance member data
	I3MediumServicePtr medium_;
	std::string mediumPropInFilename_;
	std::string mediumHistoOutFilename_;

	// logging
	SET_LOGGER("I3MediumServiceFactory");
	
  // ROOT macro
  // ClassDef(I3MediumServiceFactory,0);
};

#endif // I3_MEDIUM_SERVICE_FACTORY_H_INCLUDED
