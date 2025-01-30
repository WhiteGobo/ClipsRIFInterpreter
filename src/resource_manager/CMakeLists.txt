add_library(clipsrif_resource_manager SHARED
	resource_manager.cc
	resource_manager.h
	rema_functions.cc
	additional_user_functions.cc
	rema_functions.h
)

add_compile_options(-fPIC) #or it fails to link clips

target_include_directories(clipsrif_resource_manager PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
#${PROJECT_BINARY_DIR})

set_target_properties(clipsrif_resource_manager PROPERTIES
	PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/resource_manager.h
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
	resources/RDFSEntailment.clp
	resources/OwlDirect.clp
	resources/extra_functions.clp
	resources/SimpleEntailment.clp
)

target_link_libraries(clipsrif_resource_manager PUBLIC
	ffi_clips_interface
)

target_link_libraries(clipsrif_resource_manager PRIVATE
	clipsrifinterpreter::rc
	n3parser
)


set(installable_libs ${installable_libs} clipsrif_resource_manager PARENT_SCOPE)

#install(TARGETS clipsrif_resource_manager
#	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)
#if(BUILD_SHARED_LIBS)
#	install(TARGETS clipsrif_resource_manager
#		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#	)
#endif()
