project(opentp-example)

# find and link boost
find_package(Boost REQUIRED COMPONENTS system filesystem)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR})

# find and link DevIL
find_package(DevIL REQUIRED)

link_directories(${IL_LIBRARY})
include_directories(${IL_INCLUDE_DIR})

# link opentp

include_directories("../opentp/include")

file(GLOB OPENTP_EXAMPLE_SOURCES "source/*.cpp")

add_executable(opentp-example ${OPENTP_EXAMPLE_SOURCES})

target_link_libraries(opentp-example opentp ${Boost_LIBRARIES} ${IL_LIBRARY})
add_dependencies(opentp-example opentp)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/textures"
    COMMAND cmake -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/textures" "${CMAKE_CURRENT_BINARY_DIR}/textures"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/textures"
)

add_custom_target(opentp-example-textures ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/textures)
