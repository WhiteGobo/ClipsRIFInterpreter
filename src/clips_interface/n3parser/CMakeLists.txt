add_library(n3parser STATIC
	n3parser.c
	n3parser.h
	init_data.c
)

target_include_directories(n3parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(n3parser PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/../interface"
)

set_target_properties(n3parser PROPERTIES
  PUBLIC_HEADER n3parser.h
  OUTPUT_NAME "n3parser"
)

target_link_libraries(n3parser PRIVATE
	clips
)
