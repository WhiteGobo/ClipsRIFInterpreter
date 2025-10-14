add_library(crifi_utilities STATIC
	measure_activations.c
	crifi_utilities.h
)

target_include_directories(crifi_utilities
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_link_libraries(crifi_utilities PUBLIC
	#ffi_clips_interface
	crifi_public_interface
)
