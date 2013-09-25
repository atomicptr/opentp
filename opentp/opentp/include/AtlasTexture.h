#ifndef __OpenTP__AtlasTexture__
#define __OpenTP__AtlasTexture__

#include <iostream>
#include <string>

using namespace std;

class AtlasTexture {
    
public:
    AtlasTexture(string, int, int);
    ~AtlasTexture();
    
    string get_name();
    int get_width();
    int get_height();
    int get_square_pixels();
    
    //Image get_image();
private:
    const string name;
    const int width;
    const int height;
    const int square_pixels;
    
};

#endif /* defined(__OpenTP__AtlasTexture__) */
