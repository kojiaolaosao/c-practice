cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

#set(YAML_INCLUDE_DIR /usr/local/include/yaml-cpp)
#set(YAML_INCLUDE_LIB /usr/local/lib/libyaml-cpp.so)
set(YAML_INCLUDE_DIR /home/qiwentao/build_libs/include/yaml-cpp)
set(YAML_INCLUDE_LIB /home/qiwentao/build_libs/lib/libyaml-cpp.so)

message(${YAML_INCLUDE_LIB})

include_directories(${YAML_INCLUDE_DIR})

add_executable(untitled main.cpp)
add_executable(segTree segTree.cpp)
add_executable(a a.cpp)
add_executable(fact factMain.cpp Chapter6.h fact.cpp)


add_executable(test classtest/test.cpp)
link_libraries(classTest::lib)

target_link_libraries(segTree ${YAML_INCLUDE_LIB})