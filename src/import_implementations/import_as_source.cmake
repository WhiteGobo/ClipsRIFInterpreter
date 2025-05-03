#use add_custom_command
set(CRIFI_COMPILE_RESOURCES_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/import_as_source_script.cmake" PARENT_SCOPE)
set(CRIFI_COMPILE_RESOURCES_SKELETON "${CMAKE_CURRENT_SOURCE_DIR}/import_as_source_script_skel.h.in" PARENT_SCOPE)

function(compile_resources name outputfile)
	set(options )
	set(oneValueArgs FUNCTIONNAME SOURCEDIR)
	set(multiValueArgs TARGETS )
	cmake_parse_arguments(PARSE_ARGV 0 arg
		"${options}" "${oneValueArgs}" "${multiValueArgs}"
	)
	if(DEFINED arg_FUNCTIONNAME)
		set(opt_functionname "${arg_FUNCTIONNAME} ")
		#string(APPEND opt_args "-Dfunctionname=${arg_FUNCTIONNAME} ")
	else()
		set(opt_functionname "${name}_add_importlocations")
	endif()
	if(DEFINED arg_SOURCEDIR)
		set(sourcedir "${arg_SOURCEDIR}")
	else()
		set(sourcedir "${CMAKE_CURRENT_SOURCE_DIR}")
	endif()
	list(LENGTH arg_TARGETS length)
	math(EXPR qq "${length} % 2")
	#message(WARNING "compile_resources with name: ${name} (${length} ${arg_TARGETS})")
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

	set(TESTDATA_OUTPUT "compile_import_as_source_${name}")
	#message(FATAL_ERROR "asdf ${dependencies}")
	add_custom_command(
		OUTPUT ${outputfile}
		COMMAND ${CMAKE_COMMAND} -Dname=${name} -Dskeleton=${CRIFI_COMPILE_RESOURCES_SKELETON} -Doutputfile="${outputfile}" -Dsourcedir=${sourcedir} -Dname=${name} -Dtargets="${arg_TARGETS}" -Dfunctionname=${opt_functionname} -P ${CRIFI_COMPILE_RESOURCES_SCRIPT}
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
