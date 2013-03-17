cmake_minimum_required (VERSION 2.6)
project (NLang)

if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set (CMAKE_CXX_FLAGS "-std=c++11")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	set (CMAKE_CXX_FLAGS "-std=c++0x")
endif()

include_directories(${CMAKE_SOURCE_DIR})

add_executable(type_test types.cc types_test.cc)
add_custom_command(TARGET type_test POST_BUILD COMMAND type_test)

add_executable(simpletest_test simpletest_test.cc)
add_custom_command(TARGET simpletest_test POST_BUILD COMMAND simpletest_test)
