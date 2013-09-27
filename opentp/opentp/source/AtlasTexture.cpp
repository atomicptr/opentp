#include "AtlasTexture.h"

AtlasTexture::AtlasTexture(string name, int width, int height) :
    name(name),
    width(width),
    height(height),
    square_pixels(width * height) {
}

AtlasTexture::~AtlasTexture() {
}

const string AtlasTexture::get_name() const {
    return name;
}

const int AtlasTexture::get_width() const {
    return width;
}

const int AtlasTexture::get_height() const {
    return height;
}

const int AtlasTexture::get_square_pixels() const {
    return square_pixels;
}
