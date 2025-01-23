cmake_minimum_required(VERSION 3.14)

project(clips_rif_interpreter_library VERSION 0.1.0 LANGUAGES C CXX)

option(LINKED_CLIPS_LIB "Build with linked clips library" ON)
set(CLIPS_LIBRARY OFF CACHE FILEPATH
	"Location of clips library. can be autolocated")
set(CLIPS_HEADER /usr/include/clips CACHE PATH "\
Location of clips rules header files, used when building with clips \
as linked library"
)

include(FetchContent)

#Patch adds CMakeLists.txt to clips
if(LINKED_CLIPS_LIB)
	if(CLIPS_LIBRARY)
		set(clips_library_path ${CLIPS_LIBRARY})
	else()
		find_library(clips_library_path clips REQUIRED)
	endif()
	add_library(clips SHARED IMPORTED)
	set_property(TARGET clips
		PROPERTY IMPORTED_LOCATION ${clips_library_path})
	#include_directories(/usr/include/clips)
	target_include_directories(clips INTERFACE
		$<BUILD_INTERFACE:${CLIPS_HEADER}>
	#	#$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mylib>
	)
else()
	add_compile_options(-fPIC) #or it fails to link clips
	FetchContent_Declare(
		clips
		#DOWNLOAD_EXTRACT_TIMESTAMP TRUE #May fail if behind URL
		URL https://sourceforge.net/projects/clipsrules/files/CLIPS/6.4.1/clips_core_source_641.zip
		URL_HASH MD5=3c470a99fa25981d802e63c205c27593
		#PATCH_COMMAND cp -a ${CMAKE_CURRENT_SOURCE_DIR}/clips_update/. <SOURCE_DIR>/
		PATCH_COMMAND patch -s -p0 -d <SOURCE_DIR>/../ < ${CMAKE_CURRENT_SOURCE_DIR}/clips.patch
	)
	FetchContent_MakeAvailable(clips)
endif()



add_subdirectory(ntriples_parser)
add_subdirectory(clips_interface)
add_subdirectory(resource_manager)
add_subdirectory(generate_crifi_script)

enable_testing()
set(INSTALL_GTEST OFF)
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

#option(BUILD_SHARED_LIBS "Build using shared libraries" ON)
