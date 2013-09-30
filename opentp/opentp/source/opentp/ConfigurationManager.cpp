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

#include <opentp/ConfigurationManager.hpp>

namespace opentp {

    ConfigurationManager::ConfigurationManager() {
        this->config_file_path = path(ConfigurationManager::get_config_filepath());
        
        if(!exists(this->config_file_path)) {
            this->create_empty_config_file();
        }
        
        this->reload_configs();
    }

    ConfigurationManager::~ConfigurationManager() {
    }

    string ConfigurationManager::get_config_directory() {
    #if defined(__APPLE__)
        path p = path(getenv("HOME"));
        p /= "Library/Application Support/opentp";
    #elif defined(__linux__)
        path p = path(getenv("HOME"));
        p /= ".opentp";
    #elif defined(_WIN32)
        path p = path(getenv("APPDATA"));
        
        p /= "opentp";
    #endif
        
        create_directories(p);
        
        return p.string();;
    }

    string ConfigurationManager::get_config_filepath() {
        path p = path(ConfigurationManager::get_config_directory()) / "opentp_config.xml";
        
        return p.string();
    }

    void ConfigurationManager::reload() {
        this->reload_configs();
    }

    void ConfigurationManager::reload_configs() {
        XMLDocument document;
        
        document.LoadFile(this->config_file_path.string().c_str());
        
        XMLElement *root = document.RootElement();
        
        XMLElement *atlas_name_element = root->FirstChildElement("atlas-name");
        
        this->atlas_name = atlas_name_element->GetText() ? atlas_name_element->GetText() : "opentp_atlas";
        this->atlas_output_format = root->FirstChildElement("atlas-output-format")->GetText();
        this->atlas_data_format = root->FirstChildElement("atlas-data-format")->GetText();
        this->atlas_size_width = atoi(root->FirstChildElement("atlas-width")->GetText());
        this->atlas_size_height = atoi(root->FirstChildElement("atlas-height")->GetText());
        this->imagemagick_path = root->FirstChildElement("imagemagick-path")->GetText();
        this->graphicsmagick_path = root->FirstChildElement("graphicsmagick-path")->GetText();
    }

    void ConfigurationManager::create_empty_config_file() const {
        this->save_file("opentp_atlas", "png", "xml", 512, 512, "convert", "gm");
    }

    void ConfigurationManager::save_file(string name, string output_format, string data_format, int width, int height,
                   string im_path, string gm_path) const {
        
        XMLDocument doc;
        
        XMLDeclaration *declaration = doc.NewDeclaration();
        
        XMLElement *root_node = doc.NewElement("opentp-config");
        
        XMLElement *atlas_name = doc.NewElement("atlas-name");
        XMLElement *atlas_output_format = doc.NewElement("atlas-output-format");
        XMLElement *atlas_data_format = doc.NewElement("atlas-data-format");
        XMLElement *atlas_width = doc.NewElement("atlas-width");
        XMLElement *atlas_height = doc.NewElement("atlas-height");
        XMLElement *imagemagick_path = doc.NewElement("imagemagick-path");
        XMLElement *graphicsmagick_path = doc.NewElement("graphicsmagick-path");
        
        stringstream sswidth;
        stringstream ssheight;
        
        sswidth << width;
        ssheight << height;
        
        XMLText *atlas_name_text = doc.NewText(name.c_str());
        XMLText *atlas_output_format_text = doc.NewText(output_format.c_str());
        XMLText *atlas_data_format_text = doc.NewText(data_format.c_str());
        XMLText *atlas_width_text = doc.NewText(sswidth.str().c_str());
        XMLText *atlas_height_text = doc.NewText(ssheight.str().c_str());
        XMLText *imagemagick_path_text = doc.NewText(im_path.c_str());
        XMLText *graphicsmagick_path_text = doc.NewText(gm_path.c_str());
        
        atlas_name->LinkEndChild(atlas_name_text);
        atlas_output_format->LinkEndChild(atlas_output_format_text);
        atlas_data_format->LinkEndChild(atlas_data_format_text);
        atlas_width->LinkEndChild(atlas_width_text);
        atlas_height->LinkEndChild(atlas_height_text);
        imagemagick_path->LinkEndChild(imagemagick_path_text);
        graphicsmagick_path->LinkEndChild(graphicsmagick_path_text);
        
        root_node->LinkEndChild(atlas_name);
        root_node->LinkEndChild(atlas_output_format);
        root_node->LinkEndChild(atlas_data_format);
        root_node->LinkEndChild(atlas_width);
        root_node->LinkEndChild(atlas_height);
        root_node->LinkEndChild(imagemagick_path);
        root_node->LinkEndChild(graphicsmagick_path);
        
        doc.LinkEndChild(declaration);
        
        doc.LinkEndChild(root_node);
        
        doc.SaveFile(ConfigurationManager::get_config_filepath().c_str());
    }

    string ConfigurationManager::get_atlas_name() const {
        return this->atlas_name;
    }

    string ConfigurationManager::get_atlas_output_format() const {
        return this->atlas_output_format;
    }

    string ConfigurationManager::get_atlas_data_format() const {
        return this->atlas_data_format;
    }

    int ConfigurationManager::get_atlas_size_width() const {
        return this->atlas_size_width;
    }

    int ConfigurationManager::get_atlas_size_height() const {
        return this->atlas_size_height;
    }

    string ConfigurationManager::get_imagemagick_path() const {
        return this->imagemagick_path;
    }

    string ConfigurationManager::get_graphicsmagick_path() const {
        return this->graphicsmagick_path;
    }

    void ConfigurationManager::set_atlas_name(string name) {
        this->save_file(name, atlas_output_format, atlas_data_format, atlas_size_width,
                        atlas_size_height, imagemagick_path, graphicsmagick_path);
        this->reload_configs();
    }

    void ConfigurationManager::set_atlas_output_format(string output_format) {
        this->save_file(atlas_name, output_format, atlas_data_format, atlas_size_width,
                        atlas_size_height, imagemagick_path, graphicsmagick_path);
        this->reload_configs();
    }

    void ConfigurationManager::set_atlas_data_format(string data_format) {
        this->save_file(atlas_name, atlas_output_format, data_format, atlas_size_width,
                        atlas_size_height, imagemagick_path, graphicsmagick_path);
        this->reload_configs();
    }

    void ConfigurationManager::set_atlas_size_width(int width) {
        this->save_file(atlas_name, atlas_output_format, atlas_data_format, width,
                        atlas_size_height, imagemagick_path, graphicsmagick_path);
        this->reload_configs();
    }

    void ConfigurationManager::set_atlas_size_height(int height) {
        this->save_file(atlas_name, atlas_output_format, atlas_data_format, atlas_size_width,
                        height, imagemagick_path, graphicsmagick_path);
        this->reload_configs();
    }

    void ConfigurationManager::set_imagemagick_path(string im_path) {
        this->save_file(atlas_name, atlas_output_format, atlas_data_format, atlas_size_width,
                        atlas_size_height, im_path, graphicsmagick_path);
        this->reload_configs();
    }

    void ConfigurationManager::set_graphicsmagick_path(string gm_path) {
        this->save_file(atlas_name, atlas_output_format, atlas_data_format, atlas_size_width,
                        atlas_size_height, imagemagick_path, gm_path);
        this->reload_configs();
    }
}