add_library(crifi_objects STATIC
	crifi_objects.c
	crifi_objects.h
)

set_target_properties(crifi_objects PROPERTIES
	PUBLIC_HEADER crifi_objects.h
	OUTPUT_NAME "crifi_objects"
)

target_include_directories(crifi_objects
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")


target_link_libraries(crifi_objects
	clips
)
