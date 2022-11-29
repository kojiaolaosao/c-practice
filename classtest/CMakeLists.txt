project(classTest)
message(${YAML_INCLUDE_LIB})
add_library(${PROJECT_NAME}
        SHARED
        test.cpp
        )

add_library(classTest::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})