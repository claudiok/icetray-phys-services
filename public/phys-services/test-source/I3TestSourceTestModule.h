/**
 * copyright  (C) 2004
 * the IceCube collaboration
 *  $Id: I3TestSourceTestModule.h 2601 2005-02-08 20:05:42Z olivas $
  *
 * @file I3TestSourceTestModule.h
 * @version $Revision: 1.3 $
 * @date $Date: 2005-02-08 21:05:42 +0100 (Tue, 08 Feb 2005) $
 * @author olivas
 */

#ifndef I3TESTSOURCETESTMODULE_H
#define I3TESTSOURCETESTMODULE_H

// header files
#include "icetray/I3Module.h"

class I3TestSourceTestModule : public I3Module
{
public:

  I3TestSourceTestModule(const I3Context& ctx);
  ~I3TestSourceTestModule();
  void Configure();
  
  /** 
   * We'll want to trim the geometry everytime it gets updated.
   */ 
  void Physics(I3FramePtr frame);

private:
  
  /**
   *default constructor, assignment operator, and copy constructor
   * declared private to prevent use
   */
  I3TestSourceTestModule();
  I3TestSourceTestModule(const I3TestSourceTestModule& source);
  I3TestSourceTestModule& operator=(const I3TestSourceTestModule& source);

  unsigned  nObjects_;
  string mapName_;

  SET_LOGGER("I3TestSourceTestModule");
  
};  // end of class I3TestSourceTestModule

#endif 