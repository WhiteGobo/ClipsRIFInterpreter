set(MODELA "${CMAKE_CURRENT_BINARY_DIR}/modelA.clp")
add_custom_command(OUTPUT ${MODELA}
	COMMAND generate_builtin_model "--modelA" > " ${MODELA}"
	DEPENDS generate_builtin_model
)

#add_dependencies(hello_test ${MODELA})

#install(FILES ${MODELA}
#	TYPE DATA
#)
