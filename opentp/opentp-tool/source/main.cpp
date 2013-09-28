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
    OpenTP tp;
    
    string texture_directory = "textures";
    string atlas_destination_directory = "atlas";
    string atlas_name = "opentp_atlas";
    string atlas_output_format = "png";
    string atlas_data_format = "json";
    int atlas_size_width = 512;
    int atlas_size_height = 512;
    bool verbose = false;
    
    const string imagemagick_path = "/usr/bin/convert";
    const string graphicsmagick_path = "/usr/bin/gm";
    
    options_description description(
        "OpenTP v" +
        tp.get_version() +
        "\n\n" +
        "Usage: opentp-tool --textures TEXTURES_DIR --output OUTPUT_DIR");
    
    // generic options
    options_description generic("Generic options");
    
    generic.add_options()
        ("help,?", "this help message")
        ("version,v", "print OpenTP version")
    ;
    
    // atlas generation options
    options_description atlas_generation("Atlas generation");
    
    atlas_generation.add_options()
        ("verbose", "be verbose")
        ("textures,t", value<string>(), "get textures from <directory>")
        ("output,o", value<string>(), "place the output into <directory>")
        ("width,w", value<int>(), "set atlas width (only width will set height to the same value)")
        ("height,h", value<int>(), "set atlas height (only height will set width to the same value)")
        ("name,n", value<string>(), "atlas name (eg. open_atlas_0.png)")
    ;
    
    // configurations
    options_description config("Configuration");
    
    config.add_options()
        ("set-size", "set default altas size (eg. 512 512)")
        ("set-output-format", "set default output format (eg. png, jpg)")
        ("set-data-format", "set default data format (eg. json, xml)")
    ;
    
    description.add(generic);
    description.add(atlas_generation);
    //description.add(config);
    
    variables_map map;
    
    try {
        store(parse_command_line(argc, argv, description), map);
    } catch (const boost::program_options::error &e) {
        cerr << "OpenTP: " << e.what() << endl;
        return 1;
    }
    
    notify(map);
    
    if(map.count("version")) {
        cout << "OpenTP v" << tp.get_version() << endl;
        return 0;
    }
    
    // if user gives a --textures argument
    if(map.count("textures")) {
        texture_directory = map["textures"].as<string>();
        
        // and an output argument :D
        if(map.count("output")) {
            atlas_destination_directory = map["output"].as<string>();
        } else {
            // output directory is at the same level as the texture directory
        }
    // if user gives a --output argument without --textures
    } else if(map.count("output")) {
        //texture_directory = current_directory;
        atlas_destination_directory = map["output"].as<string>();
    } else {
        cout << description << endl;
        return 1;
    }
    
    if(map.count("verbose")) {
        verbose = true;
    }
    
    if(map.count("width")) {
        atlas_size_width = map["width"].as<int>();
        
        if(map.count("height")) {
            atlas_size_height = map["height"].as<int>();
        } else {
            // if no height defined, use width instead
            atlas_size_height = map["width"].as<int>();
        }
    // no width? but height?
    } else if(map.count("height")) {
        atlas_size_width = map["height"].as<int>();
        atlas_size_height = map["height"].as<int>();
    }
    
    if(map.count("name")) {
        atlas_name = map["name"].as<string>();
    }
    
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
