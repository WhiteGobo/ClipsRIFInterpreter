add_library(crifi_time SHARED
	crifi_time.c
	crifi_timedata.c
)

target_include_directories(crifi_time PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

#target_include_directories(crifi_time PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../interface/")

set_target_properties(crifi_time PROPERTIES
  PUBLIC_HEADER crifi_time.h
  OUTPUT_NAME "crifi_time"
)

target_include_directories(crifi_time PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../interface/")

target_link_libraries(
	crifi_time PRIVATE
	clips
	n3parser
	crifi_numeric
)
