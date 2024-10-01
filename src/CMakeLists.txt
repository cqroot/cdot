configure_file(config.h.in config.h)
target_include_directories(cdot PRIVATE ${PROJECT_BINARY_DIR}/src)

add_subdirectory(cmd)
add_subdirectory(dotfile)

target_sources(cdot PRIVATE main.c)
target_include_directories(cdot PRIVATE .)
