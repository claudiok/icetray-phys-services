#ifndef I3MCCALIBRATIONSERVICEFACTORY_H
#define I3MCCALIBRATIONSERVICEFACTORY_H
/*
 * class: I3MCCalibrationServiceFactory
 *
 * Version $Id: I3MCCalibrationServiceFactory.h 11148 2005-10-03 21:55:04Z pretz $
 *
 * Date: 17 Feb 2004
 *
 * (c) IceCube Collaboration
 */

class I3Context;

#include "icetray/I3ServiceFactory.h"
class I3MCCalibrationService;

using namespace std;

class I3MCCalibrationServiceFactory
: public I3ServiceFactory
{
 public:

  I3MCCalibrationServiceFactory(const I3Context& context);

  virtual ~I3MCCalibrationServiceFactory();

  virtual bool InstallService(I3Context& services);

  virtual void Configure();

 private:

  shared_ptr<I3MCCalibrationService> calibration_;

  I3MCCalibrationServiceFactory
    (const I3MCCalibrationServiceFactory& rhs); // stop default
  I3MCCalibrationServiceFactory operator=
    (const I3MCCalibrationServiceFactory& rhs); // stop default


   SET_LOGGER("I3MCCalibrationServiceFactory");
};

#endif 
