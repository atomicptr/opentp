#ifndef __OPENTP__IMAGE_H__
#define __OPENTP__IMAGE_H__

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

#define cimg_display 0
#include "CImg.h"

using namespace std;
using namespace cimg_library;
using namespace boost::filesystem;

class Image {
    
public:
    ~Image();
    
    static Image* new_image(int, int);
    static Image* from_file(string);
    
    void paste(Image*, int, int);
    void save(path, path) const;
    
    const int get_width() const;
    const int get_height() const;
    const CImg<unsigned char> *get_image() const;
    
private:
    Image();
    Image(Image&);
    Image(CImg<unsigned char>*);
    const Image& operator=(Image&);
    
    CImg<unsigned char> *image;
    
};

#endif
