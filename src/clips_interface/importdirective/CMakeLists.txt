add_library(crifi_import STATIC
	crifi_import.c
	crifi_import.h
	interpretation.c
	interpretations.h
	init_data.c
)

target_include_directories(crifi_import PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(crifi_import PRIVATE ${CRIFI_SHARED_HEADER})

target_link_libraries(crifi_import PUBLIC
	clips
)

set_target_properties(crifi_import PROPERTIES
	PUBLIC_HEADER crifi_import.h
	OUTPUT_NAME "crifi_import"
)
