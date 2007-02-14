#ifndef PHYSSERVICES_I3EVENTCOUNTER_H
#define PHYSSERVICES_I3EVENTCOUNTER_H

#include "icetray/I3TrayHeaders.h"
#include "icetray/I3Module.h"
#include <fstream>

class I3EventCounter : public I3Module
{
 public:
  I3EventCounter(const I3Context& ctx);
  ~I3EventCounter() {};
  void Configure();
  void Physics(I3FramePtr frame);
  void DetectorStatus(I3FramePtr frame);
  void Geometry(I3FramePtr frame);
  void Calibration(I3FramePtr frame);
  void Finish();

 private:
  I3EventCounter();
  I3EventCounter(const I3EventCounter& source);
  I3EventCounter& operator=(const I3EventCounter& source);

  /**
   * Parameter: name of output histogram file
   */
  unsigned int physCount_, statusCount_, geometryCount_, calibCount_;
  unsigned int counterStep_;

  /**
   * Parameter: how many physics events to process
   */
  unsigned int nevents_;

  /**
   * Parameter: whether to dump current frame to screen
   */
  bool dump_;

  std::string path_,fmt_;
  ostream *out;
  char buffer[200];




  SET_LOGGER("I3EventCounter");
};

#endif
