GoddamnEngine
=============
The [GoddamnEngine](http://goddamnengine.com) is cross-platform next-generation-ready realtime game engine. 
Goal of this project is the creation of the most minimalistic full-featured game development framework that surpasses most three-A engines. Project contains a very small core, but is intended to be very flexible and extensible.
Work is in progress now.

Features
--------
 - Minimalistic but flexible code design: engine is not as monstrous and clumsy piece of code as the others are.
 - Support of the most modern platforms: Windows (Phone & RT), OS X & iOS, Linux & Android, XBox One & PlayStation4, HTML5 (via Emscripten).
 - Advanced rendering pipeline: DirectX ~~12~~ and 11, ~~AMD Mantle~~, ~~Apple Metal~~, OpenGL and OpenGL(ES).
 - Entirely written in native languages: C/C++11, Objective-C/C++.

License
-------
GoddamnEngine is free for noncommercial usage and for independent developers with monthly revenue less then 10K$.
For more detailed information see ["LICENSE.txt"](https://github.com/GoddamnIndustries/GoddamnEngine/blob/master/LICENSE.txt) or visit our [licensing page](http://goddamnengine.com/licensing).

Installation
------------
 - Download [**the source code**](https://github.com/GoddamnIndustries/GoddamnEngine). You can do it by forking the official repository on GitHub.
 - Download and unzip to the engine location [**the required dependencies**](http://fixme.com) files. Replace files on prompt.
 - Perform next platform-dependent steps to finish installation.

### Windows.
 - Make sure you have [Visual Studio 2015 / 2013](http://www.visualstudio.com/) installed. 2013 edition requires additional C++ compiler set, the [Visual C++ Compiler November 2013 CTP](http://www.microsoft.com/en-us/download/details.aspx?id=41151).
 - Run the **SetupGoddamnSDK.bat** inside the _GoddamnEngine_ directory. It should take less than a minute to generate the project files.

### OS X & Linux.
 - Make sure you have [Mono Development Kit (MDK)](http://www.mono-project.com/) installed.
 - Execute from a terminal **SetupGoddamnSDK.sh** inside the _GoddamnEngine_ directory. It should take less than a minute to generate the project files.

### Cross-compilation and etc.
Setup script 