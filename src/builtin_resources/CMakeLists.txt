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
add_custom_target(modelA.clp ALL
	COMMAND generate_builtin_model "--modelA" > modelA.clp
	DEPENDS generate_builtin_model
)
add_custom_target(modelAchecker.clp ALL
	COMMAND generate_builtin_model "--modelAchecker" > modelAchecker.clp
	DEPENDS generate_builtin_model
)
