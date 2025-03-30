#CMAKE_CURRENT_SOURCE_DIR and CMAKE_CURRENT_BINARY_DIR will be transferred
#from where the script is called
if(IS_ABSOLUTE "${outputfile}")
else()
	set(outputfile "${CMAKE_CURRENT_BINARY_DIR}/${outputfile}")
endif()
message(WARNING "qwertz ${outputfile} ${name} ${targets} ${CMAKE_CURRENT_SOURCE_DIR}")

file(WRITE "${outputfile}" "brubru\n")
while(${length} GREATER 0)
	list(POP_FRONT arg_TARGETS first second)
	message(WARNING "A: ${first} B: ${second}")
	list(LENGTH arg_TARGETS length)

	file(APPEND "${outputfile}" "brubru @first@ @second@\n")
endwhile()
