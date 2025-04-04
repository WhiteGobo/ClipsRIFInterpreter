cmake_minimum_required(VERSION 3.5)
set(self "CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SCRIPT")

if(NOT DEFINED outputfile)
	message(FATAL_ERROR "${self} needs outputfile to be set (-D...=value)")
endif()
if(NOT DEFINED CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SKELETON)
	message(FATAL_ERROR "${self} needs CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SKELETON to be set (-D...=value)")
endif()
if(NOT DEFINED inputclipsscript)
	message(FATAL_ERROR "${self} needs inputclipsscript to be set (-D...=value)")
endif()
if(NOT DEFINED sourcedir)
	message(FATAL_ERROR "${self} needs sourcedir to be set (-D...=value)")
endif()
if(NOT DEFINED init_graph_name)
	message(FATAL_ERROR "${self} needs init_graph_name to be set (-D...=value)")
endif()

if(IS_ABSOLUTE ${inputclipsscript})
	set(src "${inputclipsscript}")
else()
	find_file(src NAMES ${inputclipsscript} HINTS ${sourcedir} NO_CACHE)
endif()
if(NOT src)
	message(FATAL_ERROR "Couldnt find clips script \"${inputclipsscript}\" at ${sourcedir}")
endif()

set(inputclipsscript_memory_name "${init_graph_name}_script_memory")

file(READ "${src}" bytes HEX)
string(REGEX REPLACE "(..)" "\\\\x\\1" script_memory "${bytes}")
string(LENGTH "${bytes}" n_bytes2)
math(EXPR n_bytes "${n_bytes2} / 2")

configure_file(
	${CRIFI_IMPLEMENT_CLIPS_PROGRAM_IN_BUILD_SKELETON}
	${outputfile})
