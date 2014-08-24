#include "src/chrome_open_tabs.h"
#include "src/util/home_dir.h"
#include <node.h>
#include <v8.h>

#ifdef __APPLE__
  std::string pathToSession = "/Library/Application Support/Google/Chrome/Default/Current Session";
#elif __linux
  std::string pathToSession = "/.config/google-chrome/Default/Current Session";
#endif


using namespace v8;

Handle<Value> getTabs(const Arguments& args){  
  std::string homeDir = getHomeDir();
  // the mac path..
  auto tabs = getOpenTabs(homeDir + pathToSession);

  HandleScope handle_scope;
  Handle<Array> tabArr = Array::New(tabs.size());

  int i = 0;
  for(Tab t : tabs){
    tabArr->Set(i, String::New(t.tabPath.c_str()));
    i++;
  }
  return handle_scope.Close(tabArr);
  
}

void init(Handle<Object> target){
  NODE_SET_METHOD(target, "getOpenTabs", getTabs);
}

NODE_MODULE(chromeTabs, init);
