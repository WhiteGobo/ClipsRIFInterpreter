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

add_executable(
  hello_test
  hello_test.cc
  testcases_test.cc
)

target_link_libraries(hello_test PRIVATE
  GTest::gtest_main
  ffi_clips_interface
  ntriplesParser
  clipsrif_resource_manager
  crifi_test::rc
)

#deprecated and replaced by cmakrerc:
foreach(TESTASSET
		"data/Frames-conclusion.ntriples"
		"data/Frames-premise.ntriples"
		"data/Assert-conclusion.ntriples"
		"data/Assert-premise.ntriples"
		"data/AssertRetract-conclusion.ntriples"
		"data/AssertRetract-premise.ntriples"
	)
	configure_file(${TESTASSET} ${TESTASSET})
endforeach()

include(GoogleTest)
gtest_discover_tests(hello_test)

