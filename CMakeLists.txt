cmake_minimum_required (VERSION 2.6)
project (NLang)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost COMPONENTS unit_test_framework REQUIRED)

include_directories(${CMAKE_SOURCE_DIR} ${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(type_test types.cc types_test.cc)
target_link_libraries(type_test)
add_custom_command(TARGET type_test POST_BUILD COMMAND type_test)