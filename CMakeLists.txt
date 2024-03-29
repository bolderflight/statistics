cmake_minimum_required(VERSION 3.14)
# Project information
project(Statistics
  VERSION 4.0.4
  DESCRIPTION "Statistics algorithms and classes."
  LANGUAGES CXX
)
include(FetchContent)
# Fetch circular buffer
FetchContent_Declare(
  circle_buf
  GIT_REPOSITORY https://github.com/bolderflight/circle_buf.git
  GIT_TAG v4.0.2
)
FetchContent_MakeAvailable(circle_buf)
# Add the library target
add_library(statistics INTERFACE)
# Link circular buffer
target_link_libraries(statistics
  INTERFACE
    circle_buf
)
# Setup include directories 
target_include_directories(statistics INTERFACE src/)

# Example and unit testing if this project is built separately
if (PROJECT_NAME STREQUAL CMAKE_PROJECT_NAME)
  # Add the example target
  add_executable(stats_example examples/cmake/stats_example.cc)
  # Add the includes
  target_include_directories(stats_example PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  # Link libraries to the example target
  target_link_libraries(stats_example
    PRIVATE 
      statistics
  )
  # Fetch google test
  include(FetchContent)
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY 	https://github.com/google/googletest.git
    GIT_TAG 				release-1.12.1
  )
  FetchContent_MakeAvailable(googletest)
  enable_testing()
  include(GoogleTest)
  # Add the test target
  add_executable(stats_test tests/stats_test.cc)
  # Add the includes
  target_include_directories(stats_test PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
  )
  # Link libraries to the test target
  target_link_libraries(stats_test
    PRIVATE 
      statistics
      gtest_main 
      gtest
      gmock
  )
  # Discover unit tests
  gtest_discover_tests(stats_test)
endif()
