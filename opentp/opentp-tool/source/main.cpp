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
#include <boost/filesystem.hpp>

#include <opentp/OpenTP.hpp>
#include <opentp/ConfigurationManager.hpp>

using namespace std;
using namespace boost::program_options;
using namespace boost::filesystem;

using namespace opentp;

int main(int argc, char **argv) {
    OpenTP tp;
    ConfigurationManager config;
    
    // set default values
    string texture_directory = "textures";
    string atlas_destination_directory = "atlas";
    string atlas_name = config.get_atlas_name();
    string atlas_output_format = config.get_atlas_output_format();
    string atlas_data_format = config.get_atlas_data_format();
    int atlas_size_width = config.get_atlas_size_width();
    int atlas_size_height = config.get_atlas_size_height();
    bool verbose = false;
    bool be_quiet = false;
    
    const string imagemagick_path = config.get_imagemagick_path();
    const string graphicsmagick_path = config.get_graphicsmagick_path();
    
    bool changed_configs = false;
    
    // create program_options
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
        ("quiet", "tell the program to make no noise, if verbose is enabled this option is ignored")
        ("textures,t", value<string>(), "get textures from <directory>")
        ("output,o", value<string>(), "place the output into <directory>")
        ("width,w", value<int>(), "set atlas width (only width will set height to the same value)")
        ("height,h", value<int>(), "set atlas height (only height will set width to the same value)")
        ("name,n", value<string>(), "atlas name (eg. 'open_atlas' for a file like this: open_atlas_0.png)")
    ;
    
    // configurations
    options_description config_description("Configuration (this commands save default settings, not usable for on the fly changes)");
    
    config_description.add_options()
        ("set-name", value<string>(), "set default altas name (eg. opentp_atlas)")
        ("set-output-format", value<string>(), "set default output format (eg. png, jpg)")
        ("set-data-format", value<string>(), "set default data format (eg. json, xml)")
        ("set-width", value<int>(), "set default altas width (eg. 512)")
        ("set-height", value<int>(), "set default altas height (eg. 512)")
        ("set-convert-path", value<string>(), "set path to convert (eg. /usr/bin/convert)")
        ("set-gm-path", value<string>(), "set path to gm (eg. /usr/bin/gm)")
    ;
    
    description.add(generic);
    description.add(atlas_generation);
    description.add(config_description);
    
    variables_map map;
    
    // catch program_options related errors
    try {
        store(parse_command_line(argc, argv, description), map);
    } catch (const boost::program_options::error &e) {
        cerr << "OpenTP: " << e.what() << endl;
        return 1;
    }
    
    notify(map);
    
    // if user wants to see the version, do nothing else
    if(map.count("version")) {
        cout << "OpenTP v" << tp.get_version() << endl;
        return 0;
    }
    
    // save configurations, stop execution
    if(map.count("set-name")) {
        string val = map["set-name"].as<string>();
        
        config.set_atlas_name(val);
        
        cout << "opentp config: changed default name from '" << atlas_name << "' to '" << val << "'." << endl;
        
        changed_configs = true;
    }
    
    if(map.count("set-output-format")) {
        string val = map["set-output-format"].as<string>();
        
        config.set_atlas_output_format(val);
        
        cout << "opentp config: changed default output-format from '" << atlas_output_format << "' to '" << val << "'." << endl;
        
        changed_configs = true;
    }
    
    if(map.count("set-data-format")) {
        string val = map["set-data-format"].as<string>();
        
        config.set_atlas_data_format(val);
        
        cout << "opentp config: changed default data-format from '" << atlas_data_format << "' to '" << val << "'." << endl;
        
        changed_configs = true;
    }
    
    if(map.count("set-width")) {
        int val = map["set-width"].as<int>();
        
        config.set_atlas_size_width(val);
        
        cout << "opentp config: changed default width from '" << atlas_size_width << "' to '" << val << "'." << endl;
        
        changed_configs = true;
    }
    
    if(map.count("set-height")) {
        int val = map["set-height"].as<int>();
        
        config.set_atlas_size_height(val);
        
        cout << "opentp config: changed default height from '" << atlas_size_height << "' to '" << val << "'." << endl;
        
        changed_configs = true;
    }
    
    if(map.count("set-convert-path")) {
        string val = map["set-convert-path"].as<string>();
        
        config.set_imagemagick_path(val);
        
        cout << "opentp config: changed default ImageMagick path from '" << imagemagick_path << "' to '" << val << "'." << endl;
        
        changed_configs = true;
    }
    
    if(map.count("set-gm-path")) {
        string val = map["set-gm-path"].as<string>();
        
        config.set_graphicsmagick_path(val);
        
        cout << "opentp config: changed default GraphicsMagick from '" << graphicsmagick_path << "' to '" << val << "'." << endl;
        
        changed_configs = true;
    }
    
    if(changed_configs) {
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
            path new_atlas_dir = path(texture_directory) / "../atlas";
            
            atlas_destination_directory = new_atlas_dir.string();
        }
    // if user gives a --output argument without --textures
    } else if(map.count("output")) {
        texture_directory = current_path().string();
        atlas_destination_directory = map["output"].as<string>();
    } else {
        cout << description << endl;
        return 1;
    }
    
    if(map.count("verbose")) {
        verbose = true;
    } else if(map.count("quiet")) {
        be_quiet = true;
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
    
    // if user specified an alternative name
    if(map.count("name")) {
        atlas_name = map["name"].as<string>();
    }
    
    // if verbose is enabled, print all options
    if(verbose) {
        cout << "Configurations:" << endl;
        cout << "\tatlas-name = " << atlas_name << endl;
        cout << "\ttexture_directory = " << texture_directory << endl;
        cout << "\tatlas_destination_directory = " << atlas_destination_directory << endl;
        cout << "\tatlas_output_format = " << atlas_output_format << endl;
        cout << "\tatlas_data_format = " << atlas_data_format << endl;
        cout << "\tatlas_size: = (" << atlas_size_width << ", " << atlas_size_height << ")" << endl;
        cout << "\timagemagick_path = " << imagemagick_path << endl;
        cout << "\tgraphicsmagick_path = " << graphicsmagick_path << endl;
        
    }
    
    tp.set_texture_directory(texture_directory);
    tp.set_atlas_destination_directory(atlas_destination_directory);
    tp.set_atlas_name(atlas_name);
    tp.set_atlas_output_format(atlas_output_format);
    tp.set_atlas_data_format(atlas_data_format);
    tp.set_atlas_size(atlas_size_width, atlas_size_height);
    tp.set_verbose(verbose);
    tp.set_quiet(be_quiet);
    
    tp.set_imagemagick_path(imagemagick_path);
    tp.set_graphicsmagick_path(graphicsmagick_path);
    
    tp.generate_atlas();
    
    return 0;
}
