cmake_minimum_required(VERSION 3.5)

message(INFO "Use ${name}_add_importlocations to add import capabilities "
	"to graph.")

#CMAKE_CURRENT_SOURCE_DIR and CMAKE_CURRENT_BINARY_DIR will be transferred
#from where the script is called
if(IS_ABSOLUTE "${outputfile}")
else()
	set(outputfile "${CMAKE_CURRENT_BINARY_DIR}/${outputfile}")
endif()
separate_arguments(targets)

if(NOT DEFINED functionname)
set(functionname "${name}_add_importlocations")
endif()
list(LENGTH targets length)
set(contextid "0")
set(importmethods "")
set(memory "")
set(syntax "\"http://www.w3.org/ns/formats/Turtle\"")
while(${length} GREATER 0)
	list(POP_FRONT targets first second)

	unset(src)
	find_file(src NAMES ${second} HINTS ${sourcedir} NO_CACHE)

	list(LENGTH targets length)

	set(loading_context "${name}_contextid${contextid}")
	set(loading_context_length "${loading_context}_length")
	math(EXPR contextid "${contextid} + 1")

	#read file and represent content in bytes
	file(READ "${src}" bytes HEX)
	string(REGEX REPLACE "(..)" "\\\\x\\1" chars "${bytes}")
	string(LENGTH "${bytes}" n_bytes2)
	math(EXPR n_bytes "${n_bytes2} / 2")
	#math(EXPR remainder "${n_bytes} % 5") # <-- '5' is the grouping count from above
	#set(cleanup_re "$")
	#set(cleanup_sub )
	#while(remainder)
	#	set(cleanup_re "(..)${cleanup_re}")
	#	set(cleanup_sub "'\\\\x\\${remainder}',${cleanup_sub}")
	#	math(EXPR remainder "${remainder} - 1")
	#endwhile()
	#if(NOT cleanup_re STREQUAL "$")
	#	string(REGEX REPLACE "${cleanup_re}" "${cleanup_sub}" chars "${chars}")
	#endif()

	string(APPEND importmethods "\t{.id=\"${first}\", .method=${name}_import_method, .context=${loading_context}, .cleanup=NULL, .syntax=${syntax}},\n")
	string(APPEND memory "static char *${loading_context} = \"${chars}\";\n")
	#string(APPEND memory "static size_t @loading_context_length@ = @n_bytes@;\n")
endwhile()
configure_file(${skeleton} ${outputfile})
