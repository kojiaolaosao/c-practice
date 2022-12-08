cmake_minimum_required(VERSION 3.16)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

#set(YAML_INCLUDE_DIR /usr/local/include/yaml-cpp)
#set(YAML_INCLUDE_LIB /usr/local/lib/libyaml-cpp.so)
set(YAML_INCLUDE_DIR /home/qiwentao/build_libs/include/yaml-cpp)
set(YAML_INCLUDE_LIB /home/qiwentao/build_libs/lib/libyaml-cpp.so)
set(MYSQL_CONN_DIR /home/qiwentao/build_libs/mysqljdbc/include)
set(MYSQL_CONN_LIB /home/qiwentao/build_libs/mysqljdbc/lib64/libmysqlcppconn.so)
set(JSON_LIB /usr/local/lib/libboost_json.so)


include_directories(${YAML_INCLUDE_DIR})
include_directories(${MYSQL_CONN_DIR})

link_libraries(classTest::lib)
link_libraries(${YAML_INCLUDE_LIB})

add_subdirectory(jdbc)
add_subdirectory(classtest)

add_executable(untitled main.cpp)
add_executable(segTree segTree.cpp)
add_executable(a a.cpp)
add_executable(fact factMain.cpp Chapter6.h fact.cpp)
add_executable(test classtest/test.cpp)
add_executable(httpServer http_server/server.cpp)
add_executable(tm test_mysql.cpp)

target_link_libraries(test PUBLIC mysqlclient)
target_link_libraries(tm
        ${MYSQL_CONN_LIB}
        ${JSON_LIB}
#        boost_json
        pthread
        )
target_link_libraries(httpServer
        pthread
)