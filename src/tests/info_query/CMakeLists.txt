
add_executable(info_query_test
	info_query_test.cc
	example_info_query.h
	example_info_query.c
)

target_link_libraries(info_query_test PRIVATE
	GTest::gtest_main
	ffi_clips_interface
	info_query
)

include(GoogleTest)
gtest_discover_tests(info_query_test)
