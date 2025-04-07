set(CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SCRIPT
	"${CMAKE_CURRENT_SOURCE_DIR}/crifi_implement_clips_program_in_build_script.cmake"
	PARENT_SCOPE)
set(CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SKELETON
	"${CMAKE_CURRENT_SOURCE_DIR}/crifi_implement_clips_program_in_build_skel.h.in"
	PARENT_SCOPE)

#[[[
# Generate a method to load a graph with logic loaded as described
# in the given logic_input.
#
# RETRIEVE_SCRIPT : this will define a function, from which the script
#	can be loaded.
#
#]]
function(crifi_implement_clips_program_in_build
		outputfile
		inputclipsscript
		init_graph_name)

	set(options )
	set(oneValueArgs RETRIEVE_SCRIPT)
	set(multiValueArgs )
	cmake_parse_arguments(PARSE_ARGV 0 arg
		"${options}" "${oneValueArgs}" "${multiValueArgs}"
	)
	if(DEFINED arg_RETRIEVE_SCRIPT)
		message(FATAL_ERROR "RETRIEVE_SCRIPT isnt implemented for "
				"crifi_implement_clips_program_in_build yet.")
	endif()

	set(dependencies "")
	list(APPEND dependencies ${CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SCRIPT})
	list(APPEND dependencies ${CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SKELETON})
	list(APPEND dependencies ${inputclipsscript})

	add_custom_command(
		OUTPUT ${outputfile}
		COMMAND ${CMAKE_COMMAND} 
			-Doutputfile=${outputfile}
			-Dinputclipsscript=${inputclipsscript}
			-DCRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SKELETON=${CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SKELETON}
			-Dinit_graph_name=${init_graph_name}
			-Dsourcedir=${CMAKE_CURRENT_SOURCE_DIR}
			-P ${CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SCRIPT}
		DEPENDS ${dependencies}
	)
	return()

endfunction()
