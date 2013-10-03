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

project(opentp-tool)

# find and link boost
find_package(Boost REQUIRED COMPONENTS system filesystem program_options)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR})

# if not windows, find X11
if(NOT WIN32)
    find_package(X11 REQUIRED)

    link_directories(${X11_LIBRARIES})
    include_directories(${X11_INCLUDE_DIR})
endif(NOT WIN32)

# find libPNG
find_package(PNG 1.4 REQUIRED)

include_directories(${PNG_INCLUDE_DIR})

# find Threads
find_package(Threads)

# link opentp
include_directories("../opentp/libs/cimg")
include_directories("../opentp/include")

file(GLOB OPENTP_TOOL_SOURCES "source/*.cpp")

add_executable(opentp-tool ${OPENTP_TOOL_SOURCES})

target_link_libraries(opentp-tool opentp ${Boost_LIBRARIES} ${X11_LIBRARIES} ${PNG_LIBRARY} ${CMAKE_THREAD_LIBS_INIT})
add_dependencies(opentp-tool opentp)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/textures"
    COMMAND cmake -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/textures" "${CMAKE_CURRENT_BINARY_DIR}/textures"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/textures"
)

add_custom_target(opentp-tool-textures ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/textures)
