project(opentp)

set(Boost_USE_STATIC_LIBS ON)
find_package(Boost REQUIRED COMPONENTS system filesystem)

link_directories(${Boost_LIBRARY_DIRS})
include_directories(${Boost_INCLUDE_DIR})

include_directories("include")

file(GLOB_RECURSE OPENTP_SOURCES
    "source/*.cpp"
)

file(GLOB_RECURSE OPENTP_HEADERS
    "include/*.h"
)

file(GLOB OPENTP
    "source/*.cpp"
    "include/*.h"
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

target_link_libraries(opentp ${Boost_LIBRARIES})
