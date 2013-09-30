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

#ifndef __OPENTP__ATLAS_DATA_HPP__
#define __OPENTP__ATLAS_DATA_HPP__

#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

#include <opentp/AtlasTexture.hpp>
#include <libs/tinyxml2.h>

using namespace std;
using namespace boost::filesystem;

using namespace opentp;

namespace opentp {
    
    class AtlasData {

        struct AtlasDataItem {
            int x;
            int y;
            int width;
            int height;
            string name;
            string atlas_file;
        };
    
    public:
        AtlasData();
        ~AtlasData();
    
        void add(AtlasTexture*, string, int, int);
        void save(path, string) const;
        void dump() const;
    
    private:
        vector<AtlasDataItem*> items;
    
        void save_xml(path) const;
    };
}

#endif

