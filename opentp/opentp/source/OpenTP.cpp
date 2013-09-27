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

OpenTP::~OpenTP() {
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

void OpenTP::delete_list_with_images(list<AtlasTexture*>* supported_images) {
    for(AtlasTexture* ar : *supported_images) {
        delete ar;
    }
    
    delete supported_images;
}

void OpenTP::generate_atlas() {
    list<AtlasTexture*> *supported_images = this->get_supported_images();
    
    cout << supported_images->size() << " valid images found." << endl;
    
    // sort the list by square pixels
    supported_images->sort(compare_atlas_texture);
    
    // reverse the list so that the biggest element comes first
    supported_images->reverse();
    
    unsigned int atlas_counter = 0;
    
    while(supported_images->size() > 0) {
        // coppy supported_images (this list exists only for performance reasons)
        list<AtlasTexture*> *images = new list<AtlasTexture*>(*supported_images);
        
        // TODO: create new image
        
        // delete only the list (not the images!)
        delete images;
    }
    
    // delete supported images
    this->delete_list_with_images(supported_images);
}

list<AtlasTexture*>* OpenTP::get_supported_images() {
    list<AtlasTexture*> *supported_images = new list<AtlasTexture*>;
    
    path cwd = current_path();
    string _path = "";
    
    if(exists(cwd / this->texture_directory)) {
        _path = (cwd / this->texture_directory).string();
    } else if(exists(this->texture_directory)) {
        _path = path(this->texture_directory).string();
    } else {
        throw "Error: Unknown path: " + this->texture_directory;
    }
    
    directory_iterator iterator(_path);
    
    for(; iterator != boost::filesystem::directory_iterator(); ++iterator) {
        string filename = iterator->path().filename().string();
        
        path _tmp_path = path(_path);
        
        _tmp_path /= filename;
        
        // TODO: improve this statement
        if(!(extension(_tmp_path) == ".png" || extension(_tmp_path) == ".jpg" || extension(_tmp_path) == ".gif")) {
            cout << "Unknown extension: " << extension(_tmp_path) << endl;
            continue;
        }
        
        Image *image = Image::from_file(_tmp_path.string());
        
        int width = image->get_width();
        int height = image->get_height();
        
        supported_images->push_back(new AtlasTexture(filename, _tmp_path, width, height));
        
        delete image;
    }
    
    return supported_images;
}
