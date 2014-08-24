
// currently only works on linux / mac

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include "home_dir.h"


std::string getHomeDir(){
  struct passwd *pw = getpwuid(getuid());
  const char *homedir = pw->pw_dir;
  
  return std::string(homedir);
}
