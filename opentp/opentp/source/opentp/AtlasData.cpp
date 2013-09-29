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

#include <opentp/AtlasData.hpp>

AtlasData::AtlasData() {
}

AtlasData::~AtlasData() {
    int size = items.size();
    
    for(int i = 0; i < size; i++) {
        AtlasDataItem *item = items[i];
        
        if(!item) {
            continue;
        }
        
        delete item;
        
        items[i] = NULL;
    }
}

void AtlasData::add(AtlasTexture *atlas_texture, string atlas_file, int x, int y) {
    AtlasDataItem *item = new AtlasDataItem;
    
    item->x = x;
    item->y = y;
    item->width = atlas_texture->get_width();
    item->height = atlas_texture->get_height();
    item->name = atlas_texture->get_name();
    item->atlas_file = atlas_file;
    
    items.push_back(item);
}

void AtlasData::save(path filepath, string data_format) const {
    if(data_format == "xml") {
        this->save_xml(filepath);
    } else {
        cerr << "opentp Error: Unkown data_format: " << data_format << endl;
    }
}

void AtlasData::save_xml(path filepath) const {
    XMLDocument doc;
    
    XMLDeclaration *declaration = doc.NewDeclaration();
    
    XMLElement *root_node = doc.NewElement("texture-atlas");
    
    int size = items.size();
    
    for(int i = 0; i < size; i++) {
        AtlasDataItem *item = items[i];
        
        // create new element
        XMLElement *texture = doc.NewElement("texture");
        
        texture->SetAttribute("atlas_file", item->atlas_file.c_str());
        texture->SetAttribute("name", item->name.c_str());
        
        XMLElement *position = doc.NewElement("position");
        
        position->SetAttribute("x", item->x);
        position->SetAttribute("y", item->y);
        position->SetAttribute("width", item->width);
        position->SetAttribute("height", item->height);
        
        texture->LinkEndChild(position);
        
        root_node->LinkEndChild(texture);
    }
    
    doc.LinkEndChild(declaration);
    
    doc.LinkEndChild(root_node);
    
    doc.SaveFile(filepath.c_str());
}

void AtlasData::dump() const {
    int size = items.size();
    
    cout << "Dump " << size << " items:" << endl << endl;
    
    for(int i = 0; i < size; i++) {
        AtlasDataItem *item = items[i];
        
        cout << "Item: " << item->name << ", Atlas: " << item->atlas_file << ", Size: "
            << item->width << "x" << item->height << ", Position: " << item->x << "x" << item->y << endl;
    }
}