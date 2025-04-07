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

target_link_libraries(crifi_builtin_resources PRIVATE
	ffi_clips_interface
	crifi_import_implementations
)

target_include_directories(crifi_builtin_resources PUBLIC
	"${MODELDATA_DIRECTORY}"
)
