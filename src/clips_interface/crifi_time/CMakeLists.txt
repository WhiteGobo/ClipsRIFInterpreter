add_library(crifi_time STATIC
	crifi_time.c
	crifi_timedata.c
	crifi_time.h
	crifi_timedata.h
)

target_include_directories(crifi_time PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(crifi_time PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../interface/")

set_target_properties(crifi_time PROPERTIES
	PUBLIC_HEADER crifi_time.h
	OUTPUT_NAME "crifi_time"
)

target_link_libraries(crifi_time PUBLIC
	clips
	crifi_numeric
)

target_link_libraries(crifi_time PRIVATE
	n3parser
)
