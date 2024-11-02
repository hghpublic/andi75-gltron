set(RC_NAME "gltron.ini")

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(PATH_SEPARATOR "\\\\")
    set(PREF_DIR "\\\\")
    set(SNAP_DIR "\\\\")
else()
    set(PATH_SEPARATOR "/")
    set(PREF_DIR "/")
    set(SNAP_DIR "/")
endif()


configure_file(defines.h.in defines.h @ONLY)

# target_sources(${target} PRIVATE main.c)
target_include_directories(${target} PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
set(DEFINES_H_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR} PARENT_SCOPE)
# set(DEFINES_INCLUDE_DIR ${CMAKE_CURRENT_BINARY_DIR} CAHE INTERNAL "defines.h include directory")
