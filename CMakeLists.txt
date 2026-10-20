cmake_minimum_required(VERSION 3.16)
project(scale_demo CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# clang-tidy reads build/compile_commands.json to know how each file compiles
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB SCALE_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)
add_library(scale ${SCALE_SOURCES})
target_include_directories(scale PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_compile_options(scale PRIVATE -Wall -Wextra)

enable_testing()
file(GLOB TEST_SOURCES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/tests/test_*.cpp)
foreach(test_src ${TEST_SOURCES})
  get_filename_component(test_name ${test_src} NAME_WE)
  add_executable(${test_name} ${test_src})
  target_link_libraries(${test_name} scale)
  add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()
