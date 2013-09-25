#ifndef OPENTP_H
#define OPENTP_H

#include <iostream>
#include <string>
#include <list>
#include <boost/filesystem.hpp>

#include <AtlasTexture.h>

using namespace std;
using namespace boost::filesystem;

class OpenTP {

public:
	OpenTP();
    ~OpenTP();
    
    void set_texture_directory(string);
    void set_atlas_destination_directory(string);
    void set_atlas_name(string);
    void set_atlas_output_format(string);
    void set_atlas_data_format(string);
    void set_atlas_size(int, int);
    void set_verbose(bool);
    
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
    
    void delete_supported_images(list<AtlasTexture*>*);
    list<AtlasTexture*> *get_supported_images();
    
};

#endif
