add_library(ffi_clips_interface SHARED
  ffi_clips_interface.c
  graph_engine.c
  clips_to_interface.c
)

set_target_properties(ffi_clips_interface PROPERTIES
	PUBLIC_HEADER interface/ffi_clips_interface.h
	OUTPUT_NAME "ffi_clips_interface"
)

target_include_directories(ffi_clips_interface
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/interface/")

target_include_directories(ffi_clips_interface
	PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")

target_compile_definitions(ffi_clips_interface PUBLIC DART_SHARED_LIB)


#Patch adds CMakeLists.txt to clips
add_compile_options(-fPIC) #or it fails to link clips
FetchContent_Declare(
  clips
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE #May fail if behind URL
  URL https://sourceforge.net/projects/clipsrules/files/CLIPS/6.4.1/clips_core_source_641.zip
  PATCH_COMMAND cp -a ${CMAKE_CURRENT_SOURCE_DIR}/clips_update/. <SOURCE_DIR>/
)
FetchContent_MakeAvailable(clips)

add_subdirectory(external_functions)
add_subdirectory(n3parser)
add_subdirectory(lists)
add_subdirectory(objects)

target_link_libraries(ffi_clips_interface
	clips
	external_functions
	n3parser
)
