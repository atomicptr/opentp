# Copyright (c) 2013 Christopher Kaster
#
# This file is part of OpenTP <https://github.com/Kasoki/opentp>.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

project(opentp)

# find and link boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system filesystem)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR})

# if not windows, find x11
if(NOT WIN32)
    find_package(X11 REQUIRED)

    link_directories(${X11_LIBRARIES})
    include_directories(${X11_INCLUDE_DIR})
endif(NOT WIN32)

# find libPNG
find_package(PNG REQUIRED)

include_directories(${PNG_INCLUDE_DIR})

# opentp

include_directories("include")

file(GLOB_RECURSE OPENTP_SOURCES
    "source/*.cpp"
)

file(GLOB_RECURSE OPENTP_HEADERS
    "include/*.h"
    "include/*.hpp"
)

file(GLOB OPENTP
    "source/*.cpp"
    "include/*.h"
    "include/*.hpp"
)

source_group("opentp" FILES ${OPENTP})

IF(BUILD_SHARED_LIBS)
    add_library(opentp SHARED ${OPENTP_HEADERS} ${OPENTP_SOURCES})
ELSE(BUILD_SHARED_LIB)
    IF(BUILD_STATIC_LIBS)
	add_library(opentp STATIC ${OPENTP_HEADERS} ${OPENTP_SOURCES})
    ELSE(BUILD_STATIC_LIBS)
	add_library(opentp ${OPENTP_HEADERS} ${OPENTP_SOURCES})
    ENDIF(BUILD_STATIC_LIBS)
ENDIF(BUILD_SHARED_LIBS)

target_link_libraries(opentp ${Boost_LIBRARIES} ${X11_LIBRARIES} ${PNG_LIBRARY})
