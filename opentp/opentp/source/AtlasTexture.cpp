#include "AtlasTexture.h"

AtlasTexture::AtlasTexture(string name, int width, int height) :
    name(name),
    width(width),
    height(height),
    square_pixels(width * height) {
}

string AtlasTexture::get_name() {
    return name;
}

int AtlasTexture::get_width() {
    return width;
}

int AtlasTexture::get_height() {
    return height;
}

int AtlasTexture::get_square_pixels() {
    return square_pixels;
}
