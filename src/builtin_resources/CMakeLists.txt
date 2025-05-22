set(CRIFI_RECREATE_BUILTIN_MODELS TRUE CACHE BOOL "recreate builtin models in build directory")

set(MODELDATA_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/")
set(MODELDATA_AS_HEADER_MODELA
	"${MODELDATA_DIRECTORY}/modeldata_as_header_modelA.h")

include(data_compilelist_modela.cmake) #defines compilelist_modela

compile_resources(data_modelA ${MODELDATA_AS_HEADER_MODELA}
	FUNCTIONNAME "modelA_add_importlocations"
	TARGETS ${compilelist_modela})

add_library(crifi_builtin_resources STATIC
	crifi_builtin_resources.c
	crifi_builtin_resources.h
	${MODELDATA_AS_HEADER_MODELA}
)

target_link_libraries(crifi_builtin_resources PUBLIC
	ffi_clips_interface
	crifi_import_implementations
)

target_include_directories(crifi_builtin_resources PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${MODELDATA_DIRECTORY}"
)

add_executable(generate_builtin_model
	generate_builtin_model.c
)

target_link_libraries(generate_builtin_model PRIVATE
	crifi_builtin_resources
	crifi_raptor
	crifi_graph_models
)

#include(recreate_builtin_graph_model.cmake)

#set(MODELA "${CMAKE_CURRENT_BINARY_DIR}/modelA.clp")


list(APPEND MODELNAMES "modelA" "modelAchecker")
#set(MODEL_LOCATION "${CRIFI_GRAPH_MODELS_MODELPATH}")
set(MODEL_LOCATION "${CMAKE_SOURCE_DIR}/clips_interface/graph_models")
set(PROGRAM_LOCATION "${CMAKE_CURRENT_BINARY_DIR}/generate_builtin_model")
configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/overwrite_builtin_models.cmake.in"
	"${CMAKE_BINARY_DIR}/overwrite_builtin_models.cmake"
	@ONLY
)
