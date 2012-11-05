#include "phys-services/I3Functions.h"
#include "icetray/I3TrayHeaders.h"
#include <glob.h>

std::set<std::string> I3Functions::ParseString(const std::string &bigString)
{
  std::string current;
  std::set<std::string> stringSet;
  std::string::const_iterator iter;
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

std::vector<std::string> I3Functions::ParseFilename(const std::string &bigFilename)
{
  glob_t                      g;
  int                         globval;
  int                         globflag=0;
  std::set<std::string>       string_set=ParseString(bigFilename);
  std::set<std::string>::const_iterator iter;
 
  for(iter=string_set.begin(); iter!=string_set.end(); iter++)
  {
    globval = glob((*iter).c_str(), globflag, 0, &g);
    if(globflag==0) globflag=GLOB_APPEND;
    if(globval!=0) log_fatal("glob() returned an error while checking %s",(*iter).c_str());
  }  

  std::vector<std::string> to_return(g.gl_pathv, g.gl_pathv+g.gl_pathc);
  globfree(&g);
  return(to_return);
}
