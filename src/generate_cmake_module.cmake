#set(CMAKE_INSTALL_CONFIG lib/cmake/clips_rif_interpreter CACHE PATH "\
#Location where Findclips_rif_interpreter.cmake will be installed. \
#See also CMAKE_MODULE_PATH."
#)

include(CMakePackageConfigHelpers)
#configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
#	"${CMAKE_CURRENT_BINARY_DIR}/clips_rif_interpreter-config.cmake"
#	INSTALL_DESTINATION ${CMAKE_INSTALL_CONFIG}
#	NO_SET_AND_CHECK_MACRO
#	NO_CHECK_REQUIRED_COMPONENTS_MACRO
#)
#
#install(FILES "${CMAKE_CURRENT_BINARY_DIR}/clips_rif_interpreter-config.cmake"
#	DESTINATION ${CMAKE_INSTALL_CONFIG})


configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/clips_interfaceConfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/ffi_clips_interface-config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_CONFIG}
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ffi_clips_interface-config.cmake"
	DESTINATION ${CMAKE_INSTALL_CONFIG})

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/ntriples_parserConfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/ntriples_parser-config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_CONFIG}
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/ntriples_parser-config.cmake"
	DESTINATION ${CMAKE_INSTALL_CONFIG})


configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/resource_managerConfig.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/resource_manager-config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_CONFIG}
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/resource_manager-config.cmake"
	DESTINATION ${CMAKE_INSTALL_CONFIG})
