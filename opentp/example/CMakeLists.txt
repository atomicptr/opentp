project(OpenTP_Examples)

include_directories("../opentp/include")

file(GLOB OPENTP_EXAMPLE_SOURCES "source/*.cpp")

add_executable(opentp-example ${OPENTP_EXAMPLE_SOURCES})
target_link_libraries(opentp-example opentp)
add_dependencies(opentp-example opentp)

add_custom_command(
    OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/textures"
    COMMAND cmake -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/textures" "${CMAKE_CURRENT_BINARY_DIR}/textures"
    DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/textures"
)

add_custom_target(opentp-example-textures ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/textures)
