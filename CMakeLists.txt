cmake_minimum_required(VERSION 3.13)
# Project information
project(Welford
  VERSION 1.0
  DESCRIPTION "Welford's method for streaming mean, variance, and standard deviation."
  LANGUAGES C CXX
)
# Add the library target
add_library(welford
	include/welford/welford.h
 	src/welford/welford.cc
 )
# Setup include directories 
target_include_directories(welford PUBLIC 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
 	$<INSTALL_INTERFACE:include>
)
# Example and unit testing if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
	# Add the example target
	add_executable(welford_example examples/welford_example.cc)
	# Add the includes
	target_include_directories(welford_example PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
	# Link libraries to the test target
	target_link_libraries(welford_example
		PRIVATE 
			welford
	)
	# Fetch google test
	include(FetchContent)
	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
	)
	FetchContent_MakeAvailable(googletest)
	enable_testing()
	include(GoogleTest)
	# Add the test target
	add_executable(welford_test tests/welford_test.cc)
	# Add the includes
	target_include_directories(welford_test PUBLIC 
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
	)
	# Link libraries to the test target
	target_link_libraries(welford_test
		PRIVATE 
			welford
			gtest_main 
			gtest
			gmock
	)
	# Discover unit tests
	gtest_discover_tests(welford_test)
endif()
