set(UTILS_SRC
	utils/bnode_lookup.c
	utils/bnode_lookup.h
	utils/triple_list.c
	utils/triple_list.h
	utils/pair_list.c
	utils/pair_list.h
	utils/rdf_list.c
	utils/rdf_list.h
	utils/rdf_list_internal.h
)

add_library(crifi_import STATIC
	crifi_import.c
	crifi_import.h
	${UTILS_SRC}
	interpretation.c
	interpretations.h
	init_data.c
	direct_interpretation.c
	direct_interpretation.h
	rdf_to_rif_interpretation/rdf_to_rif_interpretation.c
	rdf_to_rif_interpretation/rdf_to_rif_interpretation.h
	rdf_to_rif_interpretation/rdf_to_rif_commondata.c
	rdf_to_rif_interpretation/rdf_to_rif_commondata.h
	simple_to_owl_interpretation/simple_to_owl_interpretation.c
	simple_to_owl_interpretation/simple_to_owl_interpretation.h
	simple_to_owl_interpretation/simple_to_owl_info.h
	simple_to_owl_interpretation/simpletoowl_special_assert.c
	simple_to_owl_interpretation/simpletoowl_special_assert.h
	clipsvalue_interface.c
	clipsvalue_interface.h
	node_retriever.h
)

target_include_directories(crifi_import PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(crifi_import PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/rdf_to_rif_interpretation/"
	"${CMAKE_CURRENT_SOURCE_DIR}/simple_to_owl_interpretation/"
	"${CMAKE_CURRENT_SOURCE_DIR}/utils/"
)
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
