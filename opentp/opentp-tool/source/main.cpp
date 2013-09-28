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

#include <iostream>
#include <string>

#include <OpenTP.h>

using namespace std;

int main(int argc, char **argv) {
    const string texture_directory = "textures";
    const string atlas_destination_directory = "atlas";
    const string atlas_name = "opentp_atlas";
    const string atlas_output_format = "png";
    const string atlas_data_format = "json";
    const int atlas_size_width = 512;
    const int atlas_size_height = 512;
    const bool verbose = true;
    
    const string imagemagick_path = "/usr/bin/convert";
    const string graphicsmagick_path = "/usr/bin/gm";
    
    OpenTP *tp = new OpenTP;
    
    tp->set_texture_directory(texture_directory);
    tp->set_atlas_destination_directory(atlas_destination_directory);
    tp->set_atlas_name(atlas_name);
    tp->set_atlas_output_format(atlas_output_format);
    tp->set_atlas_data_format(atlas_data_format);
    tp->set_atlas_size(atlas_size_width, atlas_size_height);
    tp->set_verbose(verbose);
    
    tp->set_imagemagick_path(imagemagick_path);
    tp->set_graphicsmagick_path(graphicsmagick_path);
    
    tp->generate_atlas();
    
    delete tp;
    
    return 0;
}
