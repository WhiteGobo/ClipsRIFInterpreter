include(CTest)

add_subdirectory(data)

FetchContent_Declare(
	googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

set(TESTDATA_OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/testdata.h")
compile_resources(myname ${TESTDATA_OUTPUT} TARGETS
	"http://example.com/testdata#shared_bnode" importdata/shared_bnode.ttl
	"http://example.com/testdata#asdf.ttl" importdata/asdf.ttl
)


add_executable(hello_test
	hello_test.cc
	testcases_test.cc
	raptor_test.cc
	import_test.cc
	${TESTDATA_OUTPUT}
)

target_include_directories(hello_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(hello_test PRIVATE
	GTest::gtest_main
	ffi_clips_interface
	ntriplesParser
	clipsrif_resource_manager
	crifi_test::rc
	crifi_raptor
	crifi_import
	crifi_import_implementations
	info_query
)


include(GoogleTest)
gtest_discover_tests(hello_test)

add_subdirectory(info_query)
