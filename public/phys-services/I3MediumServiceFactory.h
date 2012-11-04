/**
 * Definition of I3MediumServiceFactory class
 *
 * (c) 2005
 * the IceCube Collaboration
 * $Id$
 *
 * @file I3MediumServiceFactory.h
 * @version $Revision$
 * @date $Date$
 * @author tschmidt
 */

#ifndef I3_MEDIUM_SERVICE_FACTORY_H_INCLUDED
#define I3_MEDIUM_SERVICE_FACTORY_H_INCLUDED

// forward declarations

class I3Context;

// header files

#include <string>

#include <icetray/I3ServiceFactory.h>
#include <phys-services/I3MediumService.h>
#include <icetray/I3Logging.h>

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
class I3MediumServiceFactory : public I3ServiceFactory
{
 public:
  /**
   * @brief Constructor.
   * 
   * @param context The context in which the service will exist.
   */
  explicit I3MediumServiceFactory(const I3Context& context);
  /**
   * @brief Destructor.
   */
  virtual ~I3MediumServiceFactory();
  virtual bool InstallService(I3Context& services);
  virtual void Configure();

 private:
  // private copy constructors and assignment
  I3MediumServiceFactory(const I3MediumServiceFactory &);
  I3MediumServiceFactory& operator=(const I3MediumServiceFactory &);

  // instance member data
  I3MediumServicePtr medium_;
  std::string mediumPropInFilename_;
  std::string mediumHistoOutFilename_;

  // logging
  SET_LOGGER ("I3MediumServiceFactory");
};

#endif // I3_MEDIUM_SERVICE_FACTORY_H_INCLUDED
