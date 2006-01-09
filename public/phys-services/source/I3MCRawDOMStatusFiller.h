/**
 * Definition of I3MCRawDOMStatusFiller class
 *
 * copyright  (C) 2004
 * the IceCube collaboration
 * $Id: I3MCRawDOMStatusFiller.h 6917 2005-04-26 02:56:37Z tmccauley $
 * 
 * @file I3MCRawDOMStatusFiller.h
 * @version $Revision: 1.14 $
 * @date $Date: 2005-04-25 22:56:37 -0400 (Mon , 25 Apr 2005) $
 * @author pretz
 * @author tmccauley
 */

#ifndef I3MCRAWDOMSTATUSFILLER_H
#define I3MCRAWDOMSTATUSFILLER_H

#include "phys-services/I3PhysicsModule.h"
#include "dataclasses/I3RawDOMStatus.h"

/**
 *
 * @brief This module allow you to fill the RawDOMStatus data 
 *	contained on the DetectorStatus stream by hand. 
 *	The information gets cloned for all of the IceCube
 * 	DOMs contained in the geometry.
 */
class I3MCRawDOMStatusFiller : public I3PhysicsModule
{
public:
    I3MCRawDOMStatusFiller(const I3Context&);

    void Configure();
    void DetectorStatus(I3Frame& frame);

    SET_LOGGER("I3MCRawDOMStatusFiller");

private:
    int triggerMode_;
    int lcMode_;
    
    double lcWindowPre_;
    
    double lcWindowPost_;
    
    double pmtHV_;
    double speThreshold_;

    bool atwdAOn_;
    bool atwdBOn_;
    
    bool fadcOn_;

    int atwd0Nbins_;
    int atwd1Nbins_;
    int atwd2Nbins_;
    int atwd3Nbins_;

    int fadcNbins_;
};

#endif
