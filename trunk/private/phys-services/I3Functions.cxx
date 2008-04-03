#include "phys-services/I3Functions.h"
#include "icetray/I3TrayHeaders.h"
#include <glob.h>

set<string> I3Functions::ParseString(const string &bigString)
{
  string current;
  set<string> stringSet;
  string::const_iterator iter;
  for(iter = bigString.begin(); iter != bigString.end(); iter++) {
    if(*iter==':' || *iter==',' || *iter==';') {
      stringSet.insert(current);
      current.clear();
    }
    else {
      current.push_back(*iter);
    }
  }
  if(!current.empty()) stringSet.insert(current);
  return stringSet;
}

vector<string> I3Functions::ParseFilename(const string &bigFilename)
{
  glob_t                      g;
  int                         globval;
  int                         globflag=0;
  set<string>                 string_set=ParseString(bigFilename);
  set<string>::const_iterator iter;
 
  for(iter=string_set.begin(); iter!=string_set.end(); iter++)
  {
    globval = glob((*iter).c_str(), globflag, 0, &g);
    if(globflag==0) globflag=GLOB_APPEND;
    if(globval!=0) log_fatal("glob() returned an error while checking %s",(*iter).c_str());
  }  

  vector<string> to_return(g.gl_pathv, g.gl_pathv+g.gl_pathc);
  globfree(&g);
  return(to_return);
}
