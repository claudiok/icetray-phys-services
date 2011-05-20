#ifndef I3TIMERANGE_H
#define I3TIMERANGE_H

#include <sstream>
#include "dataclasses/I3Time.h"


/**
 * @brief Currently 'Time' is just a double.  I think it'll have
 * to be changed because I don't think we get ns precision this way
 * 
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
struct I3TimeRange
{
  I3TimeRange(I3Time lower_time,
	      I3Time upper_time) : 
    lower(lower_time), upper(upper_time) {}
  
  I3TimeRange() {}
  
  I3Time lower;

  I3Time upper;

  string ToString()
  {
    ostringstream o;
    ToStream(o);
    return o.str();
  }

  void ToStream(ostream& o) const
  {
    o<<"[ I3TimeRange: \n"
     <<"Lower: \n"
     //<<ToString(lower)
     <<"\n"
     <<"Upper: \n"
     //<<ToString(upper)
     <<"\n";
  }
};

inline ostream& operator<<(ostream& o, const I3TimeRange& t)
{
  t.ToStream(o);
  return o;
}



#endif 
