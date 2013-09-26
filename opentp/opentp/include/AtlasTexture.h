#ifndef __OpenTP__AtlasTexture__
#define __OpenTP__AtlasTexture__

#include <iostream>
#include <string>

using namespace std;

class AtlasTexture {
    
public:
    AtlasTexture(string, int, int);
    ~AtlasTexture();
    
    const string get_name() const;
    const int get_width() const;
    const int get_height() const;
    const int get_square_pixels() const;
    
    //Image get_image();
private:
    const string name;
    const int width;
    const int height;
    const int square_pixels;
    
};

#endif /* defined(__OpenTP__AtlasTexture__) */
