# houdini-sop-test-model

[Houdini](http://www.sidefx.com/index.php) SOP / OBJ node which lets you choose one of the test models and generate its geometry.
![houdini-sop-test-model screenshot](http://i.imgur.com/k8aaxWM.png)

## Binaries, Houdini 15
* [Mac OS X, Houdini 15.0.416](https://github.com/ttvd/houdini-sop-test-model/releases/download/1.0/houdini.sop.test.model.15.0.416.tar.gz)

## Building

* Tested on OS X 10.11 / Windows and Houdini 15.
  * You would have to patch CMake file to get this building on Linux.
* Define HOUDINI_VERSION env variable to be the version of Houdini 15 you wish to build against (for example "15.0.313").
 Alternatively, you can have HFS env variable defined (set when you source houdini_setup).
* Generate build files from CMake for your favorite build system. For Windows builds use MSVC 2012.
* Build the SOP / OBJ Houdini dso (SOP_TestModel.dylib or SOP_TestModel.dll) and (OBJ_TestModel.dylib or OBJ_TestModel.dll).
* Place the dso in the appropriate Houdini dso folder.
  * On OS X this would be /Users/your_username/Library/Preferences/houdini/15.0/dso/
  * On Windows this would be C:\Users\your_username\Documents\houdini15.0\dso

## Usage

* Place a test model OBJ node, this will create an OBJ level node with test model SOP node inside.
* Or place a test model SOP inside any OBJ node.
* Select the type of model.
* Select the type of primitive (Polygons or Points).
* Please remember that several of these artifacts have religious or cultural significance. Don't animate or morph them, don't apply Boolean operators to them, and don't simulate nasty things happening to them (like breaking, exploding, melting, etc.).

## License

* Copyright Mykola Konyk, 2016
* Distributed under the [MS-RL License.](http://opensource.org/licenses/MS-RL)
* **To further explain the license:**
  * **You cannot re-license any files in this project.**
  * **That is, they must remain under the [MS-RL license.](http://opensource.org/licenses/MS-RL)**
  * **Any other files you add to this project can be under any license you want.**
  * **You cannot use any of this code in a GPL project.**
  * Otherwise you are free to do pretty much anything you want with this code.
