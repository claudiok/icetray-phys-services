#ifndef TIME_H
#define TIME_H

#include <sstream>

using namespace std;

/**
 * @brief Currently 'Time' is just a double.  I think it'll have
 * to be changed because I don't think we get ns precision this way
 * 
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
typedef double Time;

/**
 * @brief Currently 'Time' is just a double.  I think it'll have
 * to be changed because I don't think we get ns precision this way
 * 
 * @note THIS IS AN EXPERIMENTAL CLASS.  DON'T USE IT IF YOU'RE
 * WANTING SOMETHING PERFECTLY STABLE
 */
struct TimeRange
{
  TimeRange(Time lower_time,Time upper_time) : lower(lower_time), upper(upper_time) {}
  TimeRange() : lower(0), upper(0) {}
  Time lower;
  Time upper;
  string ToString()
  {
    ostringstream o;
    ToStream(o);
    return o.str();
  }
  void ToStream(ostream& o) const
  {
    o<<"("<<lower<<","<<upper<<")";    
  }
};

inline ostream& operator<<(ostream& o, const TimeRange& t)
{
  t.ToStream(o);
  return o;
}



#endif 
