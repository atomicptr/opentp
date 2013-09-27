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
    list<AtlasTexture*> *sp = this->get_supported_images();
    
    list<AtlasTexture*> *supported_images = new list<AtlasTexture*>;
    
    for(int i = 0; i < 5; i++) {
        supported_images->push_back(sp->front());
        sp->remove(sp->front());
    }
    
    cout << supported_images->size() << " valid images found." << endl;
    
    // sort the list by square pixels
    supported_images->sort(compare_atlas_texture);
    
    // reverse the list so that the biggest element comes first
    supported_images->reverse();
    
    unsigned int atlas_counter = 0;
    
    while(supported_images->size() > 0) {
        // coppy supported_images (this list exists only for performance reasons)
        list<AtlasTexture*> *images = new list<AtlasTexture*>(*supported_images);
        
        // create new image
        Image *atlas_image = Image::new_image(this->atlas_width, this->atlas_height);
        
        // create matrix for atlas_image
        unsigned long atlas_matrix_size = this->atlas_width * this->atlas_height;
        bool *matrix = new bool[atlas_matrix_size];
        
        // set all elements to false
        memset(matrix, false, atlas_matrix_size);
        
        // fill atlas image with textures
        for(size_t y = 0; y < atlas_height; y++) {
            
            for(size_t x = 0; x < atlas_width; x++) {
                
                // if current position is occupied, continue
                if(this->get_matrix(matrix, x, y)) {
                    continue;
                }
                
                // remove images which wouldn't fit anymore
                for(AtlasTexture *atlas_texture : *images) {
                    
                    // if image doesn't fit remove it and continue
                    if(y + atlas_texture->get_height() > atlas_height) {
                        images->remove(atlas_texture);
                        continue;
                    }
                    
                    // check if the image fits in x position
                    if(x + atlas_texture->get_width() > atlas_width) {
                        continue;
                    }
                    
                    // check if the image fits
                    if(this->image_fits(matrix, atlas_texture, x, y)) {
                        this->paste_image_into_atlas(matrix, atlas_image, atlas_texture, x, y);
                        
                        // TODO: append image to atlas_data
                        
                        // remove image from supported_images and copied array
                        supported_images->remove(atlas_texture);
                        images->remove(atlas_texture);
                    }
                }
                
                
            }
        }
        
        // create atlas_path
        stringstream ss;
        
        ss << atlas_name << "_" << atlas_counter << "." << output_format;
        
        string new_file_name = ss.str();
        
        path atlas_path = path(atlas_destination_directory) / path(new_file_name);
        
        // save atlas to file system
        atlas_image->save(atlas_path, path(atlas_destination_directory));
        
        // delete matrix
        delete [] matrix;
        
        // delete only the list (not the images!)
        delete images;
        
        // time for the next atlas ;)
        atlas_counter++;
    }
    
    // delete supported images (list and all images)
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

bool OpenTP::get_matrix(bool *matrix, int x, int y) const {
    return matrix[atlas_width * y + x];
}

void OpenTP::set_matrix(bool *matrix, int x, int y, bool value) const {
    matrix[atlas_width * y + x] = value;
}

bool OpenTP::image_fits(bool *matrix, AtlasTexture *atlas_texture, int x, int y) const {
    for(size_t local_y = 0; local_y < atlas_texture->get_height(); local_y++) {
        for(size_t local_x = 0; local_x < atlas_texture->get_width(); local_x++) {
            if(this->get_matrix(matrix, x, y)) {
                return false;
            }
        }
    }
    
    return true;
}

void OpenTP::paste_image_into_atlas(bool *matrix, Image *atlas_image, AtlasTexture *atlas_texture, int x, int y) const {
    Image *image = atlas_texture->get_image();
    
    atlas_image->paste(image, x, y);
    
    for(size_t local_y = 0; local_y < image->get_height(); local_y++) {
        for(size_t local_x = 0; local_x < image->get_width(); local_x++) {
            this->set_matrix(matrix, x, y, true);
        }
    }
}
