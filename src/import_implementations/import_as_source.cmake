#use add_custom_command
set(CRIFI_COMPILE_RESOURCES_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/import_as_source_script.cmake" PARENT_SCOPE)

function(compile_resources outputfile name)

	set(options )
	set(oneValueArgs )
	set(multiValueArgs TARGETS )
	cmake_parse_arguments(PARSE_ARGV 0 arg
		"${options}" "${oneValueArgs}" "${multiValueArgs}"
	)
	list(LENGTH arg_TARGETS length)
	math(EXPR qq "${length} % 2")
	message(WARNING "compile_resources with name: ${name} (${length} ${arg_TARGETS})")
	if(qq EQUAL 1)
		message(FATAL_ERROR "compile_resources expects pairs of "
					"identifier and file as input")
	endif()

	add_custom_command(
		OUTPUT ${TESTDATA_OUTPUT}
		COMMAND ${CMAKE_COMMAND} -Doutputfile="${TESTDATA_OUTPUT}" -Dname=testdata -Dtargets="asdf;qwer" -P ${CRIFI_COMPILE_RESOURCES_SCRIPT}
		#DEPENDS compile_resources
	)

	return()

endfunction()
#compile_resources(targetfile brubru TARGETS asdf qwer yxcv fghj)
