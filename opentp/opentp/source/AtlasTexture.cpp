#include "AtlasTexture.h"

AtlasTexture::AtlasTexture(string name, path filepath, int width, int height) :
    name(name),
    filepath(filepath),
    width(width),
    height(height),
    square_pixels(width * height) {
}

AtlasTexture::~AtlasTexture() {
}

const string AtlasTexture::get_name() const {
    return name;
}

const path AtlasTexture::get_path() const {
    return filepath;
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

Image* AtlasTexture::get_image() const {
    return Image::from_file(this->filepath.string());
}
