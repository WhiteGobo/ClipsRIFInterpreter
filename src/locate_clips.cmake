if(CLIPS_LIBRARY)
	set(clips_library_path ${CLIPS_LIBRARY})
else()
	find_library(clips_library_path
		NAMES clips
		REQUIRED)
endif()
if(CLIPS_HEADER)
	set(CLIPS_INCLUDES ${CLIPS_HEADER})
else()
	set(BASE_FIND_PATHS
		   /usr/local/include
		   /usr/include
	)
	find_path(CLIPS_INCLUDES clips.h
		HINTS ${BASE_FIND_PATHS}
		PATH_SUFFIXES clips
		REQUIRED
	)
endif()

add_library(clips SHARED IMPORTED)
set_property(TARGET clips
	PROPERTY IMPORTED_LOCATION ${clips_library_path})
target_include_directories(clips INTERFACE
        $<BUILD_INTERFACE:${CLIPS_INCLUDES}>
)

