add_library(crifi_numeric SHARED
	crifi_numeric.c
)

target_include_directories(crifi_numeric PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(crifi_numeric PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../interface/")

set_target_properties(crifi_numeric PROPERTIES
  PUBLIC_HEADER crifi_numeric.h
  OUTPUT_NAME "crifi_numeric"
)

target_link_libraries(
	crifi_numeric PRIVATE
	clips
	n3parser
)
