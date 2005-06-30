/**
 * Definition of I3MCRawDOMStatusFiller class
 *
 * copyright  (C) 2004
 * the IceCube collaboration
 * $Id: I3MCRawDOMStatusFiller.h 6917 2005-04-26 02:56:37Z tmccauley $
 *
 * @file I3MCRawDOMStatusFiller.h
 * @version $Revision: 1.14 $
 * @date $Date: 2005-04-25 22:56:37 -0400 (Mon, 25 Apr 2005) $
 * @author pretz
 * @author tmccauley
 */

#ifndef I3MCRAWDOMSTATUSFILLER_H
#define I3MCRAWDOMSTATUSFILLER_H

#include "phys-services/I3PhysicsModule.h"

/**
 * @brief This module fills the 
 * I3MCRawDetectorStatus for each 
 * DOM that it finds in the in ice geometry.
 */
class I3MCRawDOMStatusFiller : public I3PhysicsModule
{
public:
    I3MCRawDOMStatusFiller(I3Context&);

    void DetectorStatus(I3Frame& frame);

    SET_LOGGER("I3MCRawDOMStatusFiller");

private:
    double pmtHV_;
    double speThreshold_;
    
    double lcWindowUpPre_;
    double lcWindowDownPre_;
    
    double lcWindowUpPost_;
    double lcWindowDownPost_;
    
    bool atwdAOn_;
    bool atwdBOn_;
    
    bool fadcOn_;
};

#endif
