project(Jdbc)
#message(${PROJECT_SOURCE_DIR})
add_library(${PROJECT_NAME}
        SHARED
        JdbcHelper.cpp
        )

add_library(Jdbc::lib ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
