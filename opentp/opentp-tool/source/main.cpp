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
    
    OpenTP *tp = new OpenTP;
    
    tp->set_texture_directory(texture_directory);
    tp->set_atlas_destination_directory(atlas_destination_directory);
    tp->set_atlas_name(atlas_name);
    tp->set_atlas_output_format(atlas_output_format);
    tp->set_atlas_data_format(atlas_data_format);
    tp->set_atlas_size(atlas_size_width, atlas_size_height);
    tp->set_verbose(verbose);
    
    tp->generate_atlas();
    
    delete tp;
    
    return 0;
}
