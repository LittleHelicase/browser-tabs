
#ifndef CHROME_OPEN_TABS
#define CHROME_OPEN_TABS

#include <string>
#include <vector>
#include "tab.h"


/**
  * returns the open tabs of your chrome
  * NEVER try to run this in parallel it won't work...
  *
  * @param SessionFile the path to the Chrome Session File usually under 
  *   Mac: ~/Library/Application Support/Google/Chrome/Default/Current Session
  *   Linux: ~/.config/google-chrome/Default/CurrentSession
  *   Windows: I don't care...
  */
std::vector<Tab> getOpenTabs(std::string SessionFile);

#endif
