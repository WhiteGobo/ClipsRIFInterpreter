add_executable(generate_crifi_script generate_crifi_script.cc)
add_executable(oneshot_crifi_script oneshot_crifi_script.cc)

target_link_libraries(generate_crifi_script PRIVATE
	clipsrif_resource_manager
	ffi_clips_interface
	ntriplesParser
	crifi_raptor
	n3parser
)

target_link_libraries(oneshot_crifi_script PRIVATE
	ffi_clips_interface
	crifi_raptor
)
