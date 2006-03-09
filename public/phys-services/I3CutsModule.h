/**
 * $Id: I3CutsModule.h$
 * (c) 2005 IceCube Collaboration
 * @author D.Turcan
 */

#ifndef I3CUTPARAMSMODULE_H
#define I3CUTPARAMSMODULE_H

#include "icetray/I3Module.h"
#include "icetray/I3Tray.h"
#include "phys-services/I3Functions.h"
#include "dataclasses/physics/I3Particle.h"


/**
 * @brief
 * 
 */
class I3CutsModule : public I3Module
{
public:

  I3CutsModule(const I3Context& ctx);
  ~I3CutsModule() { }
  void Configure();
  void Physics(I3FramePtr frame);
  
private:
  
  I3CutsModule();
  I3CutsModule(const I3CutsModule& source);
  I3CutsModule& operator=(const I3CutsModule& source);

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
   * Named stream for my logging messages.  Allows my messages to be
   * sent to a particular log file, to be set to a special threshold, etc.
   */
  SET_LOGGER("CutsModule");

};

#endif