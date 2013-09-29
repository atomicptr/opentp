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

#ifndef __OPENTP__IMAGE_HPP__
#define __OPENTP__IMAGE_HPP__

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

#define cimg_display 0
#include <libs/CImg.h>

using namespace std;
using namespace cimg_library;
using namespace boost::filesystem;

namespace opentp {

    class Image {
        
    public:
        ~Image();
        
        static Image* new_image(int, int);
        static Image* from_file(string);
        
        void paste(Image*, int, int);
        void save(path, path) const;
        
        const int get_width() const;
        const int get_height() const;
        const CImg<unsigned char> *get_image() const;
        
    private:
        Image();
        Image(Image&);
        Image(CImg<unsigned char>*);
        const Image& operator=(Image&);
        
        CImg<unsigned char> *image;
        
    };
}

#endif
