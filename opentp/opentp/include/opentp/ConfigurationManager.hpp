#ifndef __OPENTP__CONFIGURATION_MANAGER_HPP__
#define __OPENTP__CONFIGURATION_MANAGER_HPP__

#include <iostream>
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>

#include <libs/tinyxml2.h>

using namespace std;
using namespace boost::filesystem;

using namespace tinyxml2;

class ConfigurationManager {

public:
    ConfigurationManager();
    ~ConfigurationManager();

    string get_atlas_name() const;
    string get_atlas_output_format() const;
    string get_atlas_data_format() const;
    int get_atlas_size_width() const;
    int get_atlas_size_height() const;
    string get_imagemagick_path() const;
    string get_graphicsmagick_path() const;
    
    void set_atlas_name(string);
    void set_atlas_output_format(string);
    void set_atlas_data_format(string);
    void set_atlas_size_width(int);
    void set_atlas_size_height(int);
    void set_imagemagick_path(string);
    void set_graphicsmagick_path(string);
    
    void reload();
    
    static string get_config_directory();
    static string get_config_filepath();
    
private:
    path config_file_path;
    
    string atlas_name;
    string atlas_output_format;
    string atlas_data_format;
    int atlas_size_width;
    int atlas_size_height;
    string imagemagick_path;
    string graphicsmagick_path;
    
    void reload_configs();
    void save_file(string, string, string, int, int, string, string) const;
    void create_empty_config_file() const;
    
};

#endif
