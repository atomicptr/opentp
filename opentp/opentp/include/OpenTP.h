#ifndef OPENTP_H
#define OPENTP_H

#include <iostream>
#include <string>

using namespace std;

class OpenTP {

public:
	OpenTP();
    
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
    
};

#endif
