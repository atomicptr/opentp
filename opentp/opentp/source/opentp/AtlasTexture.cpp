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

#include <opentp/AtlasTexture.hpp>

namespace opentp {

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

    bool AtlasTexture::compare_atlas_texture(AtlasTexture *first, AtlasTexture *second) {
        return (first->get_square_pixels() < second->get_square_pixels());
    }
}
