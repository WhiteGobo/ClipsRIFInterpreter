add_library(crifi_lists STATIC
	crifi_lists.c
	crifi_lists.h
	#crifi_lists_clipsvalue.c
	#crifi_lists_clipsvalue.h
)

set_target_properties(crifi_lists PROPERTIES
  PUBLIC_HEADER crifi_lists.h
  OUTPUT_NAME "crifi_lists"
)

target_include_directories(crifi_lists
	PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/")

target_include_directories(crifi_lists PRIVATE ${CRIFI_SHARED_HEADER})

target_link_libraries(crifi_lists PUBLIC
	crifi_public_interface
	crifi_objects
)

target_link_libraries(crifi_lists PRIVATE
	n3parser
)
