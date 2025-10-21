include(CTest)

#add_subdirectory(data)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(PREFIX_TESTDATA_IMPORT "http://example.com/testdata#")
set(TESTDATA_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/testdata.h")
compile_resources(testdata ${TESTDATA_OUTPUT} TARGETS
	"${PREFIX_TESTDATA_IMPORT}shared_bnode" importdata/shared_bnode.ttl
	"${PREFIX_TESTDATA_IMPORT}import_simple_to_rif" importdata/import_simple_to_rif.ttl
)


include(w3c_tests.cmake)

set(LOGDATA_HEADER "${CMAKE_CURRENT_BINARY_DIR}/logmanagment.h")
include(logmanagment.cmake)

add_subdirectory(info_query)
add_subdirectory(external_functions)
