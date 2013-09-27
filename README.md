OpenTP
=======

Open library for texture packing.

## How to install OpenTP

coming soon...

## How to compile OpenTP

Here are some guides on how to compile OpenTP on your operating system.

### Linux

coming soon...

### Mac OS X

**1)** First you need to clone this repository:

	git clone https://github.com/Kasoki/opentp.git

**2)** Now we'll install *(nearly)* all dependencies:

	brew install cmake boost libpng imagemagick graphicsmagick
	
**2.a)** If you're not using [Homebrew](http://brew.sh/) i'd recommend to do so (except you're using MacPorts or Flink, then you should able to install these packages yourself).

**3)** The **last dependency** is [XQuartz](http://xquartz.macosforge.org), which you will need to install yourself.

**4)** Now you'll need to make **convert** and **gm** (from ImageMagick and GraphicsMagick) to be global accessible on your system.

	cd /usr/bin
	sudo ln -s /usr/local/bin/convert
	sudo ln -s /usr/local/bin/gm
	
**5)** Now navigate to the directory where the *"opentp"* folder is located (The directory you were in the first step!).

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