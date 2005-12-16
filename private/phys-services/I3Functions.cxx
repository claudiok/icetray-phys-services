#include "phys-services/I3Functions.h"


set<string> I3Functions::ParseString(string bigString)
{
  string current;
  set<string> stringSet;
  string::iterator iter;
  for(iter = bigString.begin(); iter != bigString.end(); iter++) {
    if(*iter==':' || *iter==',' || *iter==';') {
      stringSet.insert(current);
      current="";
    }
    else {
      current.push_back(*iter);
    }
  }
  if(current != "") stringSet.insert(current);
  return stringSet;
}
