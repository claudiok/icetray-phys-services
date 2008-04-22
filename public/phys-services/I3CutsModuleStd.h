/**
 * $Id: I3CutsModuleStd.h$
 * (c) 2008 IceCube Collaboration
 * @author J.Dumm, plagiarizing from D.Turcan
 */

#ifndef I3CUTPARAMSMODULESTD_H
#define I3CUTPARAMSMODULESTD_H

#include <icetray/I3ConditionalModule.h>
#include "icetray/I3Tray.h"
#include "phys-services/I3Functions.h"
#include "dataclasses/physics/I3Particle.h"

/**
 * @brief A different implementation of I3CutsModule to allow for the calculation
 * of "Direct" quantities (Ndir, Sdir, Ldir) in 5 standard windows.  It also only
 * uses the first hits or pulses in the hit or pulsemap to calculate direct 
 * quantities but it still calcs everything else using all available hits or pulses.
 * The standard windows are: A [-15,15]ns
 *                           B [-15,25]ns
 *                           C [-15,75]ns
 *                           D [-15,150]ns
 *                           E [-15,250]ns
 * 
 * It also now includes Lall (length of all hits projected along track) and
 * cSize, the containment size parameter.
 */
class I3CutsModuleStd : public I3ConditionalModule
{
public:

  I3CutsModuleStd(const I3Context& ctx);
  ~I3CutsModuleStd() { }
  void Configure();
  void Physics(I3FramePtr frame);
  
private:
  
  I3CutsModuleStd();
  I3CutsModuleStd(const I3CutsModuleStd& source);
  I3CutsModuleStd& operator=(const I3CutsModuleStd& source);

  /**
   * Parameter: name(s) of the I3Particle(s) that the module writes to tree(s).
   * Multiple names can be included, separated by ",".  If no name is set,
   * all of the I3Particles from the event will be written.
   */
  string particleName_;

  /**
   * Parameter: name of the hit series map to use in the calculation of the
   * cut parameters.
   */
  string hitsName_;

  /**
   * Parameter: name of the pulse series map to use in the calculation of 
   * the cut parameters.
   */
  string pulsesName_;

  /**
   * Parameter: Optional tag for the name of the object inserted by this module 
   * into the frame.
   */
  string nameTag_;

  /**
   * Named stream for my logging messages.  Allows my messages to be
   * sent to a particular log file, to be set to a special threshold, etc.
   */
  SET_LOGGER("I3CutsModuleStd");

};

#endif
