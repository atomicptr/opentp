project(OpenTP)

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
