/**
 * copyright  (C) 2004
 * the IceCube collaboration
 *  $Id$
  *
 * @file I3TestSourceTestModule.h
 * @version $Revision$
 * @date $Date$
 * @author olivas
 */

#ifndef I3TESTSOURCETESTMODULE_H
#define I3TESTSOURCETESTMODULE_H

// header files
#include <string>
#include "icetray/I3Module.h"
#include "icetray/I3Frame.h"
#include "icetray/OMKey.h"
#include "dataclasses/I3Map.h"

template <class T> 
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

  std::string mapName_;

  SET_LOGGER("I3TestSourceTestModule");
  
};  // end of class I3TestSourceTestModule

template <class T>
I3TestSourceTestModule<T>::I3TestSourceTestModule(const I3Context& ctx) : 
  I3Module(ctx),
  mapName_("Default")
{
  AddOutBox("OutBox");
  
  AddParameter("MapName", 
	       "Name of the map that contains the objects", 
	       mapName_);
}

template <class T>
I3TestSourceTestModule<T>::~I3TestSourceTestModule() {
}

// transitions
template <class T>
void I3TestSourceTestModule<T>::Configure() {
  GetParameter("MapName", mapName_);
}

#endif 
