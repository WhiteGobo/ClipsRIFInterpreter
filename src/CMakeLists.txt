cmake_minimum_required(VERSION 3.14)

project(clips_rif_interpreter_library VERSION 0.0.1 LANGUAGES C CXX)

include(FetchContent)

add_subdirectory(ntriples_parser)
add_subdirectory(clips_interface)
add_subdirectory(resource_manager)

enable_testing()
add_subdirectory(tests)

#Copying assets
set(REL_ASSETPATH_CLIPSSCRIPTS ./
	CACHE STRING "relative Path where to scripts. wont override ASSETPATH_CLIPSSCRIPTS.")
set(ASSETPATH_CLIPSSCRIPTS ${PROJECT_BINARY_DIR}/${REL_ASSETPATH_CLIPSSCRIPTS}
	CACHE PATH "absolute path where to put scripts. will be created from REL_ASSETPATH_CLIPSSCRIPTS")
message(VERBOSE "Copying clips scripts to:${ASSETPATH_CLIPSSCRIPTS}")
message(STATUS "${PROJECT_BINARY_DIR}\n${ASSETPATH_CLIPSSCRIPTS}\n${REL_ASSETPATH_CLIPSSCRIPTS}")

file(COPY assets DESTINATION ${ASSETPATH_CLIPSSCRIPTS})
#add_custom_command(TARGET ffi_clips_interface POST_BUILD
#                   COMMAND ${CMAKE_COMMAND} -E copy_directory
#		   ${CMAKE_CURRENT_SOURCE_DIR}/assets/ ${ASSETPATH_CLIPSSCRIPTS})
