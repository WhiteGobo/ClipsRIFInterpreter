#use add_custom_command
set(CRIFI_COMPILE_RESOURCES_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/import_as_source_script.cmake" PARENT_SCOPE)
set(CRIFI_COMPILE_RESOURCES_SKELETON "${CMAKE_CURRENT_SOURCE_DIR}/import_as_source_script_skel.h.in" PARENT_SCOPE)

function(compile_resources name outputfile)
	set(options )
	set(oneValueArgs FUNCTIONNAME)
	set(multiValueArgs TARGETS )
	cmake_parse_arguments(PARSE_ARGV 0 arg
		"${options}" "${oneValueArgs}" "${multiValueArgs}"
	)
	set(opt_args "")
	if(DEFINED arg_FUNCTIONNAME)
		string(APPEND opt_args "-Dfunctionname=${arg_FUNCTIONNAME} ")
	endif()
	list(LENGTH arg_TARGETS length)
	math(EXPR qq "${length} % 2")
	message(WARNING "compile_resources with name: ${name} (${length} ${arg_TARGETS})")
	if(qq EQUAL 1)
		message(FATAL_ERROR "compile_resources expects pairs of "
					"identifier and file as input")
	endif()

	set(dependencies "")
	set(tmplist ${arg_TARGETS})
	while(${length} GREATER 0)
		list(POP_FRONT tmplist first second)
		if(IS_ABSOLUTE "${second}")
			#set(dependencies "${dependencies} ${second}")
			list(APPEND dependencies ${second})
		else()
			#set(dependencies "${dependencies} ${CMAKE_CURRENT_BINARY_DIR}/${second}")
			list(APPEND dependencies ${CMAKE_CURRENT_SOURCE_DIR}/${second})
		endif()
		list(LENGTH tmplist length)
	endwhile()

	#message(FATAL_ERROR "asdf ${dependencies}")
	add_custom_command(
		OUTPUT ${TESTDATA_OUTPUT}
		COMMAND ${CMAKE_COMMAND} -Dname=${name} -Dskeleton=${CRIFI_COMPILE_RESOURCES_SKELETON} -Doutputfile="${TESTDATA_OUTPUT}" -Dsourcedir=${CMAKE_CURRENT_SOURCE_DIR} -Dname=testdata -Dtargets="${arg_TARGETS}" ${opt_args} -P ${CRIFI_COMPILE_RESOURCES_SCRIPT}
		DEPENDS ${CRIFI_COMPILE_RESOURCES_SKELETON} ${CRIFI_COMPILE_RESOURCES_SCRIPT} ${dependencies}
		COMMENT "creates a method "
			"\"bool @name@_add_importlocations(crifi_graph*)\" "
			"to implement import capabilities to the given graph. "
			"The given data can be loaded via crifi:import on "
			"the given URI"
	)
	return()

endfunction()
#compile_resources(targetfile brubru TARGETS asdf qwer yxcv fghj)
