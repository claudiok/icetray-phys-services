/**
 * Copyright (C) 2008
 * The IceCube collaboration
 * ID: $Id: I3VEMCalManipulatorFactory.h 45149 2008-05-07 05:35:44Z tilo $
 *
 * @file I3VEMCalManipulatorFactory.h
 * @version $Revision: $
 * @date $Date: 2008-05-07 01:35:44 -0400 (Mi, 07 Mai 2008) $
 * @author $Author: tilo $
 */


#ifndef PHYS_SERVICES_VEMCALMANIPULATORFACTORY_H
#define PHYS_SERVICES_VEMCALMANIPULATORFACTORY_H


#include <icetray/I3ServiceFactory.h>
#include <phys-services/I3VEMCalManipulator.h>

class I3VEMCalManipulatorFactory: public I3ServiceFactory
{
public:
    
    I3VEMCalManipulatorFactory(const I3Context& context);
    ~I3VEMCalManipulatorFactory();
    
    bool InstallService(I3Context& services);
    
    void Configure();
    
private:
    
    shared_ptr<I3VEMCalManipulator> vemCalService_;
    
    std::string inCalServiceName_;
    std::string outCalServiceName_;
    
    std::string path_;
    std::string file_;
    bool forceFile_;
    bool useDefaults_;
    
    SET_LOGGER("I3VEMCalManipulatorFactory");
};

#endif 
