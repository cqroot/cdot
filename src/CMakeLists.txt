add_subdirectory(cmd)
add_subdirectory(dotfile)

target_sources(cdot PRIVATE main.c)
target_include_directories(cdot PRIVATE .)
