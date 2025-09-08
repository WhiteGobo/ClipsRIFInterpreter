if(FALSE)
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

	add_library(raptor2 SHARED IMPORTED)

	set_property(TARGET raptor2
		PROPERTY IMPORTED_LOCATION ${RAPTOR_LIBRARY_PATH}
	)

	target_include_directories(raptor2 INTERFACE
		$<BUILD_INTERFACE:${RAPTOR_INCLUDES}>
	)
else()
	##make raptor somehow static instead
	FetchContent_Declare(
		raptor2
		#GIT_REPOSITORY https://github.com/dajobe/raptor.git
		GIT_REPOSITORY https://github.com/WhiteGobo/raptor.git
		#CMAKE_CACHE_ARGS -DBUILD_SHARED_LIBS=OFF
	)
	FetchContent_MakeAvailable(raptor2)
	target_include_directories(raptor2 PUBLIC
		$<BUILD_INTERFACE:${raptor2_SOURCE_DIR}/src>
		$<BUILD_INTERFACE:${raptor2_BINARY_DIR}/src>
	)
endif()
