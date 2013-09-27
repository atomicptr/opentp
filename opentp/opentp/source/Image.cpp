#include "Image.h"

Image::Image(CImg<unsigned char> *image) {
    this->image = image;
}

Image::~Image() {
    delete image;
}

Image* Image::new_image(int width, int height) {
    CImg<unsigned char> *image = new CImg<unsigned char>(width, height, 1, 4);
    
    return new Image(image);
}

Image* Image::from_file(string path) {
    CImg<unsigned char> *image = new CImg<unsigned char>(path.c_str());
    
    return new Image(image);
}

void Image::paste(Image *other, int x, int y) {
    this->image->draw_image(x, y, 0, 0, *other->get_image(), 1);
}

void Image::save(path filepath, path atlas_dest_dir) const {
    if(!exists(atlas_dest_dir)) {
        create_directories(atlas_dest_dir);
    }
    
    this->image->save(filepath.string().c_str());
}

const int Image::get_width() const {
    return this->image->width();
}

const int Image::get_height() const {
    return this->image->height();
}

const CImg<unsigned char> *Image::get_image() const {
    return this->image;
}
