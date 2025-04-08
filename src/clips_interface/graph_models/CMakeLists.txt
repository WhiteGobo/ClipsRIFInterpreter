set(MODEL_FIRST_HEADER "${CMAKE_CURRENT_BINARY_DIR}/first.h")
crifi_implement_clips_program_in_build(
	${MODEL_FIRST_HEADER}
	"${CMAKE_CURRENT_SOURCE_DIR}/first.clp"
	init_graph_model_first_internal
)

set(MODEL_A_HEADER "${CMAKE_CURRENT_BINARY_DIR}/modelA.h")
crifi_implement_clips_program_in_build(
	${MODEL_A_HEADER}
	"${CMAKE_CURRENT_SOURCE_DIR}/modelA.clp"
	init_graph_modelA_internal
)

set(MODEL_CHECK_A_HEADER "${CMAKE_CURRENT_BINARY_DIR}/modelcheckA.h")
crifi_implement_clips_program_in_build(
	${MODEL_CHECK_A_HEADER}
	"${CMAKE_CURRENT_SOURCE_DIR}/modelAchecker.clp"
	init_graph_modelcheckA_internal
)

add_library(crifi_graph_models STATIC
	crifi_graph_models.c
	crifi_graph_models.h
	${MODEL_A_HEADER}
	${MODEL_CHECK_A_HEADER}
	${MODEL_FIRST_HEADER}
)

target_link_libraries(crifi_graph_models PUBLIC
	clips
)

target_link_libraries(crifi_graph_models PRIVATE
	crifi_import
	#info_query
	#raptor2
)

target_include_directories(crifi_graph_models PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

target_include_directories(crifi_graph_models PRIVATE
	"${CMAKE_CURRENT_BINARY_DIR}"
	${CRIFI_SHARED_HEADER}
)

set_target_properties(crifi_graph_models PROPERTIES
	PUBLIC_HEADER crifi_graph_models.h
	OUTPUT_NAME "crifi_graph_models"
)
