add_library(crifi_time STATIC
	crifi_time.c
	crifi_time.h
	crifi_timedata.c
	crifi_timedata.h
	timedata_object.c
	timedata_object.h
	timeduration_object.c
	timeduration_object.h
	clips_to_time.c
	datenumeric.c
)

target_include_directories(crifi_time PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(crifi_time PRIVATE ${CRIFI_SHARED_HEADER})

set_target_properties(crifi_time PROPERTIES
	PUBLIC_HEADER crifi_time.h
	OUTPUT_NAME "crifi_time"
)

target_link_libraries(crifi_time PUBLIC
	clips
	crifi_numeric
	info_query
)

target_link_libraries(crifi_time PRIVATE
	n3parser
)
