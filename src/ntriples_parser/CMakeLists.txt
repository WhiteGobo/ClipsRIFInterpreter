set(PROJECT_INCLUDE_DIRECTORY      include)
set(LEX_FILE       ${CMAKE_CURRENT_SOURCE_DIR}/ntriples.lex)
set(LEX_C_SOURCE   ntriples.lex.c)
set(LEX_H          ${PROJECT_INCLUDE_DIRECTORY}/ntriples.lex.h)
set(YACC_FILE      ${CMAKE_CURRENT_SOURCE_DIR}/ntriples.yacc)
set(YACC_C_SOURCE  ntriples.yacc.c)
set(YACC_H         ${PROJECT_INCLUDE_DIRECTORY}/ntriples.yacc.h)
set(PUBLIC_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR}/include)


# Don't include line numbers from the .lex and .yacc files in the final binaries
# Doing so breaks CLion debugging because CLion doesn't see them as C source files
add_definitions(-P)
set(SED_STRIP_LINE_DECLS 's/^\#line.*\$$//')

add_custom_target(ntriplesLexParser DEPENDS ${LEX_H})
add_custom_command(OUTPUT ${LEX_C_SOURCE} ${LEX_H}
	DEPENDS ${LEX_FILE}
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_INCLUDE_DIRECTORY}
	COMMAND lex ARGS -d --header-file=${LEX_H} -o ${LEX_C_SOURCE} ${LEX_FILE}
	COMMAND sed ARGS -i -re ${SED_STRIP_LINE_DECLS} ${LEX_C_SOURCE}
)

add_custom_target(ntriplesParserYaccHeader DEPENDS ${YACC_H})
add_custom_command(OUTPUT  ${YACC_C_SOURCE} ${YACC_H}
	DEPENDS ${YACC_FILE}
	PRE_BUILD
	COMMAND ${CMAKE_COMMAND} -E make_directory ${PROJECT_INCLUDE_DIRECTORY}
	COMMAND yacc ARGS -d --defines=${YACC_H} -o ${YACC_C_SOURCE} ${YACC_FILE}
	COMMAND sed ARGS -i -re ${SED_STRIP_LINE_DECLS} ${YACC_C_SOURCE}
)

add_library(ntriplesParser SHARED ${LEX_C_SOURCE} ${YACC_C_SOURCE} include/ntriplesParser.h)
target_link_libraries(
  ntriplesParser
  ffi_clips_interface
  )
target_include_directories(ntriplesParser PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_INCLUDE_DIRECTORY})
target_include_directories(ntriplesParser PUBLIC "${PUBLIC_INCLUDE}")

target_compile_options(ntriplesParser PRIVATE "-Wall" "-Werror" "-Wno-unused-function") # input and yyunput are unused
