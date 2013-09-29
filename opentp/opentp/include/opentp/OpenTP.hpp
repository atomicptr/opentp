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

#ifndef OPENTP_HPP
#define OPENTP_HPP

#define OPENTP_MAJOR_VERSION 0
#define OPENTP_MINOR_VERSION 0
#define OPENTP_PATCH_VERSION 10

#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <algorithm>
#include <boost/filesystem.hpp>

#include <opentp/AtlasTexture.hpp>
#include <opentp/Image.hpp>

using namespace std;
using namespace boost::filesystem;

class OpenTP {

public:
	OpenTP();
    ~OpenTP();
    
    const string get_version() const;
    
    void set_texture_directory(string);
    void set_atlas_destination_directory(string);
    void set_atlas_name(string);
    void set_atlas_output_format(string);
    void set_atlas_data_format(string);
    void set_atlas_size(int, int);
    void set_verbose(bool);
    void set_imagemagick_path(string) const;
    void set_graphicsmagick_path(string) const;
    
    string get_imagemagick_path() const;
    string get_graphicsmagick_path() const;
    
    void generate_atlas();

private:
    string texture_directory;
    string atlas_destination_directory;
    string atlas_name;
    string output_format;
    string data_format;
    int atlas_width;
    int atlas_height;
    bool verbose;
    
    void delete_list_with_images(list<AtlasTexture*>*);
    list<AtlasTexture*> *get_supported_images();
    
    bool get_matrix(bool*, int, int) const;
    void set_matrix(bool*, int, int, bool) const;
    bool image_fits(bool*, AtlasTexture*, int, int) const;
    void paste_image_into_atlas(bool*, Image*, AtlasTexture*, int, int) const;
    
};

#endif
