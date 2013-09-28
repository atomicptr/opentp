// Copyright (c) 2013 Christopher Kaster
//
// This file is part of OpenTP <https://github.com/Kasoki/opentp>.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

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
