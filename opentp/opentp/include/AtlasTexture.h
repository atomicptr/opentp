#ifndef __OpenTP__AtlasTexture__
#define __OpenTP__AtlasTexture__

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

#include "Image.h"

using namespace std;
using namespace boost::filesystem;

class AtlasTexture {
    
public:
    AtlasTexture(string, path, int, int);
    ~AtlasTexture();
    
    const string get_name() const;
    const path get_path() const;
    const int get_width() const;
    const int get_height() const;
    const int get_square_pixels() const;
    
    Image *get_image() const;
private:
    const string name;
    const path filepath;
    const int width;
    const int height;
    const int square_pixels;
    
};

bool compare_atlas_texture(AtlasTexture*, AtlasTexture*);

#endif /* defined(__OpenTP__AtlasTexture__) */
