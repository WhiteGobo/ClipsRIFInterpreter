install(TARGETS ${installable_libs}
	EXPORT clips_rif_interpreter_targets
	INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

#foreach(tmplib ${installable_libs})
#	target_include_directories(${tmplib} INTERFACE
#	#	#$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/mylib>
#		$<INSTALL_INTERFACE:include/>  # <prefix>/include/mylib
#	)
#endforeach()

get_target_property(qq ffi_clips_interface INTERFACE_INCLUDE_DIRECTORIES)

install(EXPORT clips_rif_interpreter_targets
	FILE clips_rif_interpreter_targets.cmake
	DESTINATION ${CMAKE_INSTALL_CONFIG}
)

#install(TARGETS ffi_clips_interface
#	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
#)
#if(BUILD_SHARED_LIBS)
#	install(TARGETS ffi_clips_interface
#		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#	)
#endif()


include(CMakePackageConfigHelpers)


configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
	"${CMAKE_CURRENT_BINARY_DIR}/clips_rif_interpreter-config.cmake"
	INSTALL_DESTINATION ${CMAKE_INSTALL_CONFIG}
	NO_SET_AND_CHECK_MACRO
	NO_CHECK_REQUIRED_COMPONENTS_MACRO
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/clips_rif_interpreter-config.cmake"
	DESTINATION ${CMAKE_INSTALL_CONFIG})

if(INSTALL_CLIPS_FINDER)
	install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/locate_clips.cmake"
		DESTINATION ${CMAKE_INSTALL_CONFIG})
endif()
