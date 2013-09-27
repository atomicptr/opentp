#include "Image.h"

Image::Image(CImg<unsigned char> *image) {
    this->image = image;
}

Image::~Image() {
    delete image;
}

Image* Image::new_image(int width, int height) {
    return NULL;
}

Image* Image::from_file(string path) {
    CImg<unsigned char> *image = new CImg<unsigned char>(path.c_str());
    
    return new Image(image);
}

const int Image::get_width() const {
    return this->image->width();
}

const int Image::get_height() const {
    return this->image->height();
}
