cmake_minimum_required(VERSION 3.14)

project(clips_rif_interpreter_library VERSION 0.1.0 LANGUAGES C CXX)
add_compile_options(-g)

option(LINKED_CLIPS_LIB "Build with linked clips library" ON)
option(BUILD_TESTING "default testing" ON)
set(CLIPS_LIBRARY OFF CACHE FILEPATH
	"Location of clips library. can be autolocated")
set(CLIPS_HEADER /usr/include/clips CACHE PATH "\
Location of clips rules header files, used when building with clips \
as linked library"
)

set(CMAKE_INSTALL_CONFIG lib/cmake/clips_rif_interpreter CACHE STRING "\
Location where Findclips_rif_interpreter.cmake will be installed. \
See also CMAKE_MODULE_PATH."
)
set(installable_libs )


include(FetchContent)

FetchContent_Declare(
	raptor2
	#GIT_REPOSITORY https://github.com/dajobe/raptor.git
	GIT_REPOSITORY https://github.com/WhiteGobo/raptor.git
	CMAKE_CACHE_ARGS -DBUILD_SHARED_LIBS=OFF
	OVERRIDE_FIND_PACKAGE
)

FetchContent_MakeAvailable(raptor2)
target_include_directories(raptor2 PUBLIC
	$<BUILD_INTERFACE:${raptor2_SOURCE_DIR}/src>
	$<BUILD_INTERFACE:${raptor2_BINARY_DIR}/src>
)


#Patch adds CMakeLists.txt to clips
if(LINKED_CLIPS_LIB)
	set(INSTALL_CLIPS_FINDER ON)
	include(locate_clips.cmake)
else()
	set(INSTALL_CLIPS_FINDER OFF)
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


add_subdirectory(import_implementations)
add_subdirectory(clips_interface)
add_subdirectory(raptor_serializer)
add_subdirectory(builtin_resources)

if(BUILD_TESTING)
	enable_testing()
	set(INSTALL_GTEST OFF)
	add_subdirectory(tests)
endif()

include(install_helper.cmake)
