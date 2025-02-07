find_library(RAPTOR_LIBRARY_PATH
	NAMES raptor2
	REQUIRED)

set(BASE_FIND_PATHS
	   /usr/local/include
	   /usr/include
)

find_path(RAPTOR_INCLUDES raptor2.h
	HINTS ${BASE_FIND_PATHS}
	PATH_SUFFIXES raptor2
	REQUIRED
)

add_library(raptor SHARED IMPORTED)

set_property(TARGET raptor
	PROPERTY IMPORTED_LOCATION ${RAPTOR_LIBRARY_PATH}
)

target_include_directories(raptor INTERFACE
	$<BUILD_INTERFACE:${RAPTOR_INCLUDES}>
)
