project(CJSON)

set(SRC_CJSON
        src/cJSON.c
        )
add_library(cjson STATIC ${SRC_CJSON})
target_include_directories(cjson PUBLIC inc)
target_link_libraries(cjson -lm)


#tests
add_executable(cjson-test tests/test.c)
target_link_libraries(cjson-test cjson)

add_executable(cjson-domain-test tests/test-domain.c)
target_link_libraries(cjson-domain-test cjson)