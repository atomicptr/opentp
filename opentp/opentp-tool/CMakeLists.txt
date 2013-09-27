project(opentp-tool)

# find and link boost
find_package(Boost REQUIRED COMPONENTS system filesystem)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR})

# find X11
find_package(X11 REQUIRED)

link_directories(${X11_LIBRARIES})
include_directories(${X11_INCLUDE_DIR})

# find libPNG
find_package(PNG REQUIRED)

include_directories(${PNG_INCLUDE_DIR})

# link opentp

include_directories("../opentp/include")

file(GLOB OPENTP_TOOL_SOURCES "source/*.cpp")

add_executable(opentp-tool ${OPENTP_TOOL_SOURCES})

target_link_libraries(opentp-tool opentp ${Boost_LIBRARIES} ${X11_LIBRARIES} ${PNG_LIBRARY})
add_dependencies(opentp-tool opentp)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/textures"
    COMMAND cmake -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/textures" "${CMAKE_CURRENT_BINARY_DIR}/textures"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/textures"
)

add_custom_target(opentp-tool-textures ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/textures)
