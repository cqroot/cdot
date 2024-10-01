set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)
set(BUILD_SHARED_AND_STATIC_LIBS ON)
set(ENABLE_CJSON_TEST Off)
add_subdirectory(cJSON)

target_link_libraries(cdot cjson-static)
target_include_directories(cdot PRIVATE cJSON)
