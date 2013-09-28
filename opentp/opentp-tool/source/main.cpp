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
#include <boost/program_options.hpp>

#include <OpenTP.h>

using namespace std;
using namespace boost::program_options;

int main(int argc, char **argv) {
    options_description description("OpenTP help: Allowed options");
    
    description.add_options()
        ("help", "shows this help message")
        ("textures", value<string>(), "specify your texture directory")
        ("output", value<string>(), "sepcify an alternative output directory")
    ;
    
    variables_map map;
    store(parse_command_line(argc, argv, description), map);
    
    notify(map);
    
    // if user gives a --textures argument
    if(map.count("textures")) {
        cout << "Texture directory: " << map["textures"].as<string>() << endl;
        
        if(map.count("output")) {
            cout << "Output directory: " << map["output"].as<string>() << endl;
        }
        
        return 1;
    // if user gives a --output argument without --textures
    } else if(map.count("output")) {
        cout << "Texture directory: current-directory" << endl;
        cout << "Output directory: " << map["output"].as<string>() << endl;
    } else {
        cout << description << endl;
        return 1;
    }
    
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
    
    OpenTP tp;
    
    tp.set_texture_directory(texture_directory);
    tp.set_atlas_destination_directory(atlas_destination_directory);
    tp.set_atlas_name(atlas_name);
    tp.set_atlas_output_format(atlas_output_format);
    tp.set_atlas_data_format(atlas_data_format);
    tp.set_atlas_size(atlas_size_width, atlas_size_height);
    tp.set_verbose(verbose);
    
    tp.set_imagemagick_path(imagemagick_path);
    tp.set_graphicsmagick_path(graphicsmagick_path);
    
    tp.generate_atlas();
    
    return 0;
}
