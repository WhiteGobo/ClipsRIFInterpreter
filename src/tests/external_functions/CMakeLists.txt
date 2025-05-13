add_executable(external_functions_test
	string_test.cc
	xmlliteral_test.cc
	system_test.cc
	time_test.cc
	list_test.cc
	helper.h
	helper.cc
)

target_include_directories(external_functions_test PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

target_link_libraries(external_functions_test PRIVATE
	GTest::gtest_main
	ffi_clips_interface
	ntriplesParser
	clipsrif_resource_manager
	crifi_raptor
	crifi_import
	crifi_import_implementations
	info_query
)

include(GoogleTest)
gtest_discover_tests(external_functions_test)
