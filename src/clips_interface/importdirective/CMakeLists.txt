add_library(crifi_import STATIC
	crifi_import.c
	crifi_import.h
	interpretation.c
	interpretations.h
	init_data.c
	direct_interpretation.c
	direct_interpretation.h
	bnode_lookup.c
	bnode_lookup.h
	rdf_to_rif_interpretation.c
	rdf_to_rif_interpretation.h
	simple_to_owl_interpretation.c
	simple_to_owl_interpretation.h
	clipsvalue_interface.c
	clipsvalue_interface.h
	triple_list.c
	triple_list.h
	rdf_list.c
	rdf_list.h
)

target_include_directories(crifi_import PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(crifi_import PRIVATE ${CRIFI_SHARED_HEADER})

target_link_libraries(crifi_import PUBLIC
	clips
)

target_link_libraries(crifi_import PRIVATE
	info_query
	raptor2
	crifi_lists
	crifi_tools
)

set_target_properties(crifi_import PROPERTIES
	PUBLIC_HEADER crifi_import.h
	OUTPUT_NAME "crifi_import"
)
