
function firefoxProfileTabs(){
  var pwuid = require("pwuid");
  var fs = require("fs");
  var path = require("path");
  var home = pwuid().dir;
  // on apple 
  var profilePath;
  var AppleProfilePath = "Library/Application Support/Firefox/Profiles";
  if(fs.existsSync(path.join(home, AppleProfilePath))){
    profilePath = path.join(home,AppleProfilePath);
  }else {
    console.log("Path does not exists: " + path.join(home, AppleProfilePath));
  }
  
  var profileTabs = {};
  console.log(profilePath);
  var profileList = fs.readdirSync(profilePath);
  for(var i in profileList){
    var profile = profileList[i];
    var sessionStoreFile = path.join(profilePath,profile,"sessionstore.js");
    profileTabs[profile] = JSON.parse(fs.readFileSync(sessionStoreFile).toString());
  }
  return profileTabs;
}


var chrome = require("./build/Release/chromeTabs");

module.exports = {
    chrome: chrome.getOpenTabs,
    firefox: firefoxProfileTabs
  }
