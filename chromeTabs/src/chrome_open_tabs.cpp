#include "SNSSParser.h"
#include <fstream>
#include <string>
#include <cstdio>
#include <vector>
#include <iostream>
#include "PickleReader.h"
#include "chrome_open_tabs.h"

using namespace std;

//
// This program will display the current URLs opened and recently closed URLs in Chrome, their title and the referrer.
// It also contains a documentation about the datatypes contained in the pickle for this command id.
//
// Copyright (c) Lukas Weissenböck, 2013 <generalleemail@gmail.com>
// Chromium (c) 2012 The Chromium Authors. All rights reserved.
//
// This library is licenced under GNU Lesser General Public Licence v3
//

// The ugly new parts are mine (LittleHelicase)
// bah global variables..
Tab activeTab;
int activeTabId = -1;

std::vector<Tab> tabs;

// clean up to avoid any global mess...
void invalidateGlobals(){
  activeTabId = -1;
  tabs.clear();
}

void storeActiveTab(){
  tabs.push_back(activeTab);
}

bool callback(id_type commandId, void *commandPayload)
{
    if(commandId == 6) // updateTabNavigation
    {
        PickleReader *pickle = static_cast<PickleReader*>(commandPayload);

        // the pickle order is as follows
        // int          tabId
        // int          tabIndex
        // string       pageUrl
        // u16string    pageTitle
        // string       contentState
        // int          transitionType
        // int          typeMask
        // string       referrerUrl
        // string       originalRequestUrl
        // int          userAgentOverriden (1 = true, 0 = false)

        int tabId, tabIndex, transitionType, typeMask, userAgentOverridden;
        std::string pageUrl, contentState, referrerUrl, originalRequestUrl;
        std::u16string pageTitle;

        pickle->readInt(&tabId);
        pickle->readInt(&tabIndex);
        pickle->readString(&pageUrl);
        pickle->readString16(&pageTitle);
        pickle->readString(&contentState);
        pickle->readInt(&transitionType);
        pickle->readInt(&typeMask);
        pickle->readString(&referrerUrl);
        pickle->readString(&originalRequestUrl);
        pickle->readInt(&userAgentOverridden);

        // if we have a change of the tabId it was the last state of the Tab
        // and hence it is the active url of the tab.
        if(tabId != activeTabId){
            if(activeTabId != -1){
              storeActiveTab();
            }
            activeTabId = tabId;
        }
        activeTab.tabIndex = tabIndex;
        activeTab.tabId = tabId;
        activeTab.contentState = contentState;
        activeTab.tabPath = pageUrl;
            
    }

    return true;
}

std::vector<Tab> getOpenTabs(std::string SessionFile){
  std::ifstream in(SessionFile);
  std::cout << SessionFile << std::endl;

  if(!in.is_open())
  {
      std::cerr << "File not found!" << std::endl;
      return std::vector<Tab>();
  }

  // Get the total length of this file
  in.seekg(0, ios::end);
  size_t fileLength = in.tellg();
  in.seekg(0, ios::beg);

  char *buffer = new char[fileLength];

  in.read(buffer, fileLength);

  SNSSParser parser(buffer, fileLength, callback);
  parser.parseCommands();
  // we cannot store the last tab since we only know that it is the active tab
  // if it is the last one with the ID.
  storeActiveTab();

  delete[] buffer;
  
  std::vector<Tab> returnVal(tabs);
  invalidateGlobals();
  return returnVal;
}
