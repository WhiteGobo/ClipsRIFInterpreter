add_library(clipsrif_resource_manager SHARED
	resource_manager.cc
	resource_manager.h
	additional_user_functions.cc
)

add_compile_options(-fPIC) #or it fails to link clips

target_include_directories(clipsrif_resource_manager PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR})

set_target_properties(clipsrif_resource_manager PROPERTIES
	PUBLIC_HEADER resource_manager.h
	OUTPUT_NAME "clipsrif_resource_manager"
)

file(DOWNLOAD "https://github.com/vector-of-bool/cmrc/releases/download/2.0.1/CMakeRC.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/CMakeRC.cmake")
include("${CMAKE_CURRENT_BINARY_DIR}/CMakeRC.cmake")

cmrc_add_resource_library(
	clipsrifinterpreter-resources

	ALIAS clipsrifinterpreter::rc
	NAMESPACE clipsrifinterpreter

	resources/OwlLogic.clp
	resources/RifLogic.clp
	resources/RDFEntailment.clp
)

target_link_libraries(clipsrif_resource_manager PRIVATE
	clipsrifinterpreter::rc
	ffi_clips_interface
	n3parser
)
