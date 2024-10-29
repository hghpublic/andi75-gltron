set(PATH_SEPARATOR "\\\\")
set(PREF_DIR "\\\\")
set(RC_NAME "gltron.ini")
set(SNAP_DIR "\\\\")

configure_file(defines.h.in defines.h @ONLY)

# target_sources(${target} PRIVATE main.c)
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
