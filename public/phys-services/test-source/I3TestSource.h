/**
 * This is used for testing.  It loads a Map of I3MCHits into the frame for romeo to process.
 */

#ifndef I3TESTSOURCEMAP_H
#define I3TESTSOURCEMAP_H

#include "icetray/I3TrayHeaders.h"
#include "icetray/I3Module.h"
#include "dataclasses/I3Map.h"
#include "dataclasses/OMKey.h"
#include <string>

#include "boost/random.hpp"



template <class T>
class I3TestSource : public I3Module
{

  SET_LOGGER("I3TestSource");

  I3TestSource();
  I3TestSource(const I3TestSource&);

  I3TestSource& operator=(const I3TestSource&);

  /**
   *Key name of output map
   */
  std::string outputMapName_;

  /**
   *Number of objects to put in the map
   */
  unsigned nObjects_; 
  /**
   * Randomizes the class you want to put in the frame.
   * This is going to be very module/class specific so have
   * to give people the option of overriding its behavior.
   */
  void Randomize(T&);

  public:
  I3TestSource(const I3Context& ctx);
  ~I3TestSource(){};
  void Configure(){
    GetParameter("OutputMap",outputMapName_);
    GetParameter("NObjects",nObjects_);
  };
  void Physics(I3FramePtr frame);
};

//source code
//there's probably a better way to organize this

template <class T>
I3TestSource<T>::I3TestSource(const I3Context& ctx) : 
  I3Module(ctx),
  outputMapName_("TestSourceMap"),
  nObjects_(1)

{
  AddParameter("OutputMap","Key of the Output Map",outputMapName_);
  AddParameter("NObjects","Number of Objects to put in the Map",nObjects_);
  AddOutBox("OutBox");
}

template <class T>
void I3TestSource<T>::Physics(I3FramePtr frame)
{
  shared_ptr< I3Map<OMKey,T> > test_map(new I3Map<OMKey,T>);

  T test_object;

  boost::rand48 rng(static_cast<int>(time(0)));
  boost::uniform_smallint<int> string_rng(1,80);
  boost::uniform_smallint<unsigned int> om_rng(1,60);

  //Make a list of random om keys
  vector<OMKey> om_list;
  while(om_list.size() < nObjects_){
    int om_string = string_rng(rng);
    unsigned int om_number = om_rng(rng);
    OMKey om(om_string,om_number);
    om_list.push_back(om);
  }

  vector<OMKey>::iterator i;
  for(i=om_list.begin(); i != om_list.end(); ++i){
    Randomize(test_object);
    (*test_map)[*i] = test_object;
  }

  frame->Put(outputMapName_, test_map);
  PushFrame(frame,"OutBox");
}

#endif
