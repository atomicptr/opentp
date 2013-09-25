#include "OpenTP.h"

OpenTP::OpenTP() {
    // default values
    this->texture_directory = "textures";
    this->atlas_destination_directory = "atlas";
    this->atlas_name = "opentp_atlas";
    this->output_format = "png";
    this->data_format = "json";
    this->atlas_width = 512;
    this->atlas_height = 512;
}

void OpenTP::set_texture_directory(string texture_directory) {
    this->texture_directory = texture_directory;
}

void OpenTP::set_atlas_destination_directory(string atlas_destination_directory) {
    this->atlas_destination_directory = atlas_destination_directory;
}

void OpenTP::set_atlas_name(string atlas_name) {
    this->atlas_name = atlas_name;
}

void OpenTP::set_atlas_output_format(string output_format) {
    this->output_format = output_format;
}

void OpenTP::set_atlas_data_format(string data_format) {
    this->data_format = data_format;
}

void OpenTP::set_atlas_size(int width, int height) {
    this->atlas_width = width;
    this->atlas_height = height;
}

void OpenTP::set_verbose(bool) {
    this->verbose = true;
}

void OpenTP::generate_atlas() {
    
}
