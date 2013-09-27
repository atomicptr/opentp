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

	sudo yum install coming-soon
	
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

coming soon...

## How to use OpenTP with *INSERT_LIBRARY_NAME_HERE*

coming soon...

## Dependencies

* **boost library** (tested with 1.54.0)
* **X11 library** 
* **libPNG** (tested with 1.5.14)
* **ImageMagick** (tested with 6.8.6-3)
* **GraphicsMagick** (tested with 1.3.18)


## Licence

OpenTP is currently not open sourced (will be licenced under a open source licence soon…) at the moment you're allowed to download, try and play with OpenTP but not to distribute it in any way.

### 3rd party code

OpenTP is using CImg an awesome image processing library intern. So that means you don't have to install it. I'm not involved in CImg so it's licenced under other terms than OpenTP so please read the licence agreements here: [opentp/opentp/lib/cimg](#need-to-change)