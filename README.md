OpenTP
=======

Open library for texture packing.

## How to install OpenTP

coming soon...

## How to compile OpenTP

Here are some guides on how to compile OpenTP on your operating system.

### Linux

In this small guide i'll show you how to compile OpenTP on Ubuntu and Fedora Linux. (Yes i know the're so much more distributions, but if you're one of the guys who are using something like ArchLinux or Gentoo chances are high that you won't even need my help -> so you probably won't even read this lovely crafted guide D: )

**1)** First you need to clone this repository:

	git clone https://github.com/Kasoki/opentp.git

**2.a Ubuntu)** This is how you install the dependencies on Ubuntu:

	sudo apt-get install build-essential cmake libboost-all-dev libpng* imagemagick graphicsmagick

**2.b Fedora)** This is how you install the dependencies on Fedora:

	sudo yum install cmake boost* libX11-devel libpng* ImageMagick* GraphicsMagick*
	sudo yum groupinstall "Development Tools" "Legacy Software Development"
	
**3)** Now navigate to your *"opentp"* directory (the one you've downloaded in the first step)

	cd /path/to/opentp
	
**4)** Create a new directory and create a makefile for opentp:

	mkdir build
	cd build
	cmake ../../opentp
	
There is now a makefile in your current directory.
	


### OS X

In this small guide i'll show you how to compile OpenTP on OS X. (tested on OS X 10.8.5)

**1)** First you need to clone this repository:

	git clone https://github.com/Kasoki/opentp.git

**2.a brew)** This is how you install the dependencies using Homebrew:

	brew install cmake boost libpng imagemagick graphicsmagick

**2.b MacPorts)** This is how you install the dependencies using MacPorts (not tested).

	sudo port install cmake boost libpng ImageMagick GraphicsMagick

**2.c other)** If you're not using [Homebrew](http://brew.sh/), MacPorts, Flink or any other packet manager out there, i'd recommend you to do so. (If you ask me… **use Homebrew** :P)

**3)** The **last dependency** is [XQuartz](http://xquartz.macosforge.org), which you will need to install yourself.

**4)** Now you'll need to make **convert** and **gm** (from ImageMagick and GraphicsMagick) to be global accessible on your system.

	cd /usr/bin
	sudo ln -s /usr/local/bin/convert
	sudo ln -s /usr/local/bin/gm
	
**5)** Now navigate to your *"opentp"* directory (The one you've downloaded in the first step)

	cd /path/to/opentp

**6.a Makefile)** Make a new directory and create a project file for your IDE:

	mkdir build
	cd build
	cmake ../opentp
	
This will create a makefile for OpenTP

**6.b Xcode)** You're using Xcode? No problem :). Just do this:

	mkdir build
	cd build
	cmake -GXcode ../opentp
	
Now there is a **OpenTP.xcodeproj** file in the current directory.

### Windows

----------

**NOTE**: At this point the Windows build will compile, run and crash. There is still an unfixed bug which will make the build unusable.

----------

In this small guide i'll show how to compile OpenTP on Windows.

**1)** You'll need to clone the Github repository, usually Windows users hate to user a terminal so i try to explain it without using a terminal…

Start your favorite graphical git tool ([TortoiseGit](https://code.google.com/p/tortoisegit/) for example).

Now clone the repository **"http://github.com/Kasoki/opentp.git"** like shown in the following screenshots:

Open the right click context menu in your development directory:

![git clone](http://abload.de/img/wincomp_1myry9.png)

And now check out the URL i've mentioned above.

![checkout repo](http://abload.de/img/wincomp_283qvq.png)

**2)** CMake setup

1. Download and install [CMake](http://www.cmake.org/). **Important: You need to select "_Add CMake to the system PATH for all users_" or - if you don't have the required permissions or whatever - at least "_Add CMake to the system PATH for current user_" during the installation, or you'll get in troubles later on at compilation.**

*(The cmake setup guide is kindly provided by [Robert Böhm](http://robertboehm.net))*

**3)** Boost library setup

1. Download the [Boost C++ libraries](http://boost.org)
1. Decompress the downloaded archive. (You could use - for instance - [7-Zip](http://7-zip.org))
1. Run "bootstrap.bat" of that folder. *NOTE: You probably have to execute this using the "Developer Command Prompt" (Included in Visual Studio)*
1. Run the "b2.exe" of that folder. *NOTE: You probably have to execute this using the "Developer Command Prompt" (Included in Visual Studio)*
1. Set the environment variable BOOST_ROOT to the path of your boost directory (That contains the "bootstrap.bat" file)

*(The boost setup guide is kindly provided by [Robert Böhm](http://robertboehm.net))*

**4)** Download and install [zlib](http://gnuwin32.sourceforge.net/packages/zlib.htm)

**5)** Download and install [libPNG](http://gnuwin32.sourceforge.net/packages/libpng.htm)

**6)** Download and install [ImageMagick](http://www.imagemagick.org/) and [GraphicsMagick](http://www.graphicsmagick.org/)

**7)** Run CMake

1. Run CMake (cmake-gui).
1. At _Where is the source code_ select the folder of OpenTP with the subfolders **opentp** and **opentp-tool**.
1. At _Where to build the binaries_ select the folder where you want your binary tree (The project files). _NOTE: You shouldn't select the source folder or any subfolder of it, since it destroys the concept of splitting between binary/source tree and it may also won't work!_
1. Press "Configure" and select your desired target platform (For instance Visual Studio 10 for a Visual Studio 2011 project).
1. Press "Generate".

**Note:** If cmake can't find the libpng files you need to set the cmake path variables yourself: Set **PNG_LIBRARY** to *"C:\Program Files\GnuWin32\lib\libpng.lib"* and **PNG_INCLUDE_DIR** to *"C:\Program Files\GnuWin32\include\libpng12"*.

CMake should now be able to generate the project.

**8)** If you try to compile the project there may occur some problems:

* Visual Studio can't find a "unistd.h" - [Here is a replacement for the <unistd.h>](#)
* libpng12.dll missing - [libpng12.dll](#)
* libzlib1.dll missing - [libzlib1.dll](#)


*(The cmake setup guide is kindly provided by [Robert Böhm](http://robertboehm.net))*


## How to use OpenTP with *INSERT_LIBRARY_NAME_HERE*

coming soon...

## Dependencies

* **boost library** (tested with 1.54.0)
* **X11 library** (not required for Windows)
* **libPNG** (tested with 1.5.14)
* **ImageMagick** (tested with 6.8.6-3)
* **GraphicsMagick** (tested with 1.3.18)


## Licence

OpenTP is currently not open sourced (will be licenced under a open source licence soon…) at the moment you're allowed to download, try and play with OpenTP but not to distribute it in any way.

### 3rd party code

OpenTP is using CImg an awesome image processing library intern. So that means you don't have to install it. I'm not involved in CImg so it's licenced under other terms than OpenTP so please read the licence agreements here: [opentp/opentp/lib/cimg](#need-to-change)