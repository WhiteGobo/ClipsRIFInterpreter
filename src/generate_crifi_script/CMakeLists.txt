add_executable(generate_crifi_script generate_crifi_script.cc)

target_link_libraries(generate_crifi_script PRIVATE
	clipsrif_resource_manager
	ffi_clips_interface
	ntriplesParser
	crifi_raptor
	n3parser
)
