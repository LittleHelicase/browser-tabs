browser-tabs
============

**This package is currently not working and I'm not able to work on it.**

## Installation

You need `nodejs` and `npm` for this. Then you need `node-gyp`, you can install it
via

```
npm install -g node-gyp
```

Then you can run:

```
npm install browser-tabs
```

## Usage

Simply require the package and call it.

```
var browserTabs = require("browser-tabs");

var chromeTabs = browserTabs.chrome();
var firefoxTabs = browserTabs.firefox();
```

Where
 * .chrome() returns a simple Array of URLs
 * .firefox() returns the content of the sessionstore.js file
