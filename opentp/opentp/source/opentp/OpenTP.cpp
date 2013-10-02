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

#include <opentp/OpenTP.hpp>

namespace opentp {

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

    const string OpenTP::get_version() const {
        stringstream ss;
        
        ss << OPENTP_MAJOR_VERSION << "." << OPENTP_MINOR_VERSION << "." << OPENTP_PATCH_VERSION;
        
        return ss.str();
    };

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

    void OpenTP::set_verbose(bool verbose) {
        this->verbose = verbose;
    }

    void OpenTP::set_imagemagick_path(string convert_path) const {
        cimg::imagemagick_path(convert_path.c_str());
    }

    void OpenTP::set_graphicsmagick_path(string gm_path) const {
        cimg::graphicsmagick_path(gm_path.c_str());
    }

    string OpenTP::get_imagemagick_path() const {
        return cimg::imagemagick_path();
    }

    string OpenTP::get_graphicsmagick_path() const {
        return cimg::graphicsmagick_path();
    }


    void OpenTP::delete_list_with_images(list<AtlasTexture*>* supported_images) {
        vector<AtlasTexture*> v = vector<AtlasTexture*>(
        supported_images->begin(), supported_images->end());

        int size = v.size();

        for(int i = 0; i < size; i++) {
            AtlasTexture *ar = v[i];

        if(!ar) {
            continue;
        }

        delete ar;

        v[i] = NULL;
        }
        
        delete supported_images;
    }

    void OpenTP::generate_atlas() {
        // if verbose enabled, print version
        if(verbose) {
            cout << "opentp v" << this->get_version() << endl;
        }
        
        list<AtlasTexture*> *supported_images = this->get_supported_images();
        
        if(verbose) {
            cout << "OpenTP: " << supported_images->size() << " valid images found." << endl;
        }
            
        // sort the list by square pixels
        supported_images->sort(AtlasTexture::compare_atlas_texture);
        
        // reverse the list so that the biggest element comes first
        supported_images->reverse();
        
        unsigned int atlas_counter = 0;
        
        // create new AtlasData set
        AtlasData atlas_data_set;
        
        while(supported_images->size() > 0) {
            // coppy supported_images (this list exists only for performance reasons)
            vector<AtlasTexture*> images = vector<AtlasTexture*>(
                    supported_images->begin(), supported_images->end());
            
            // create new image
            Image *atlas_image = Image::new_image(this->atlas_width, this->atlas_height);
            
            // create matrix for atlas_image
            unsigned long atlas_matrix_size = this->atlas_width * this->atlas_height;
            bool *matrix = new bool[atlas_matrix_size];
            
            // set all elements to false
            memset(matrix, false, atlas_matrix_size);
            
            // create atlas_path
            stringstream ss;
            
            ss << atlas_name << "_" << atlas_counter << "." << output_format;
            
            string atlas_file_name = ss.str();
            
            path atlas_path = path(atlas_destination_directory) / path(atlas_file_name);
            
            // fill atlas image with textures
            for(int y = 0; y < atlas_height; y++) {
                
                for(int x = 0; x < atlas_width; x++) {
                    
                    // if current position is occupied, continue
                    if(this->get_matrix(matrix, x, y)) {
                        continue;
                    }
                    
                    // iterate through images
                    int images_size = images.size();
                    
                    for(int i = 0; i < images_size; i++) {
                        AtlasTexture *atlas_texture = images[i];
                        
                        if(!atlas_texture) {
                            continue;
                        }
                        
                        // if image doesn't fit remove it and continue
                        if(y + atlas_texture->get_height() > atlas_height) {
                            images[i] = NULL;
                            continue;
                        }
                        
                        // check if the image fits in x position
                        if(x + atlas_texture->get_width() > atlas_width) {
                            continue;
                        }
                        
                        // check if the image fits
                        if(this->image_fits(matrix, atlas_texture, x, y)) {
                            this->paste_image_into_atlas(matrix, atlas_image, atlas_texture, x, y);
                            
                            // add image to AtlasData set
                            atlas_data_set.add(atlas_texture, atlas_file_name, x, y);
                            
                            // remove image from supported_images and copied array
                            supported_images->remove(atlas_texture);
                            images[i] = NULL;
                        }
                    }
                    
                    
                }
            }
            
            // save atlas to file system
            atlas_image->save(atlas_path, path(atlas_destination_directory));
            
            // delete matrix
            delete [] matrix;
            
            // time for the next atlas ;)
            atlas_counter++;
        }
        
        // create atlas_data_set_path
        path atlas_data_set_path = path(atlas_destination_directory) / (atlas_name + "." + data_format);
        
        // save AtlasData set
        atlas_data_set.save(atlas_data_set_path, data_format);
        
        // atlas creation finished
        cout << "opentp: Finished atlas creation after %d seconds." << endl;
        
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
            cerr << "Error: Unknown path: " << this->texture_directory << endl;
        }
        
        directory_iterator iterator(_path);
        
        for(; iterator != boost::filesystem::directory_iterator(); ++iterator) {
            string filename = iterator->path().filename().string();
            
            path _tmp_path = path(_path);
            
            _tmp_path /= filename;
            
            // TODO: improve this statement
            if(!(extension(_tmp_path) == ".png" || extension(_tmp_path) == ".jpg" || extension(_tmp_path) == ".gif")) {
                if(verbose) {
                    cout << "Unknown extension: " << extension(_tmp_path) << endl;
                }
                
                continue;
            }
            
            Image *image = Image::from_file(_tmp_path.string());
            
            int width = image->get_width();
            int height = image->get_height();
            
            supported_images->push_back(new AtlasTexture(filename, _tmp_path, width, height));
            
            if(verbose) {
                cout << "found texture: " << filename << " (" << width << "x" << height << ")" << endl;
            }
            
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
        for(int local_y = 0; local_y < atlas_texture->get_height(); local_y++) {
            for(int local_x = 0; local_x < atlas_texture->get_width(); local_x++) {
                if(this->get_matrix(matrix, x + local_x, y + local_y)) {
                    return false;
                }
            }
        }
        
        return true;
    }

    void OpenTP::paste_image_into_atlas(bool *matrix, Image *atlas_image, AtlasTexture *atlas_texture, int x, int y) const {
        Image *image = atlas_texture->get_image();
        
        atlas_image->paste(image, x, y);
        
        for(int local_y = 0; local_y < image->get_height(); local_y++) {
            for(int local_x = 0; local_x < image->get_width(); local_x++) {
                this->set_matrix(matrix, x + local_x, y + local_y, true);
            }
        }
    }
}
