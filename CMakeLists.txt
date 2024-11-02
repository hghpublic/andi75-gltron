cmake_minimum_required(VERSION 3.30)



message(STATUS "DOTNET_CLI_UI_LANGUAGE: $ENV{DOTNET_CLI_UI_LANGUAGE}")

# https://sourceforge.net/projects/gltron/
project(gltron
    VERSION 0.70
    DESCRIPTION "gltron was inspired by the film tron - actually, \
more by all the games that where inspired by the film tron :-)"
    HOMEPAGE_URL "http://www.gltron.org/"
    LANGUAGES C CXX
)

include(CMakePrintHelpers)

foreach(key
  IN ITEMS
    NUMBER_OF_LOGICAL_CORES
    NUMBER_OF_PHYSICAL_CORES
    IS_64BIT
    HAS_SSE2
    OS_NAME
    OS_RELEASE
  )
  # query the item ${key} and save its value in the variable _${key}
  cmake_host_system_information(RESULT _${key} QUERY ${key})
  cmake_print_variables(_${key})
endforeach()

include(FetchContent) # once in the project to include the module

if(WIN32)
# dirent
# https://www.man7.org/linux/man-pages/man0/dirent.h.0p.html
# https://github.com/tronkko/dirent
# https://github.com/hghpublic/tronkko-dirent
include(FetchContent)
FetchContent_Declare(dirent
    # GIT_REPOSITORY https://github.com/tronkko/dirent.git
    # GIT_TAG        39c1f1bc98ef3326237d03006f35d7dd44620e43 # 1.24
    GIT_REPOSITORY https://github.com/hghpublic/tronkko-dirent.git
    GIT_TAG        e44c9dfc95fd411c357c1dbb86535edb14931cbb # 1.24
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(dirent)
endif()

if(WIN32)
# https://hsf-training.github.io/hsf-training-cmake-webpage/05-variables/index.html
# include(CMakePrintSystemInformation)
include(CMakePrintHelpers)
# cmake_print_properties(TARGETS dirent PROPERTIES
#                        LOCATION INTERFACE_INCLUDE_DIRECTORIES)
cmake_print_properties(TARGETS dirent
PROPERTIES
    INCLUDE_DIRECTORIES
    INTERFACE_INCLUDE_DIRECTORIES
)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(libmikmod REQUIRED IMPORTED_TARGET libmikmod)
pkg_check_modules(libmodplug REQUIRED IMPORTED_TARGET libmodplug)
pkg_check_modules(ogg REQUIRED IMPORTED_TARGET ogg)

# https://cmake.org/cmake/help/latest/module/FindGLEW.html
find_package(GLEW REQUIRED)
find_package(FLAC CONFIG REQUIRED)
# find_package(libmikmod REQUIRED)
# find_package(libmodplug REQUIRED)
find_package(Ogg CONFIG REQUIRED)
find_package(PNG REQUIRED)
find_package(Vorbis CONFIG REQUIRED)
# find_package(Lua REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
if(WIN32)
find_package(dirent REQUIRED)
endif()
find_package(OpenGL REQUIRED)

# SDL_sound
# https://github.com/icculus/SDL_sound
FetchContent_Declare(SDL2_sound
    GIT_REPOSITORY https://github.com/hghpublic/icculus-SDL_sound.git
    GIT_TAG        99d19f4f2a755801592cdc63700cd1e47926ae68 # SDL_sound/2.0.3/gltron
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SDL2_sound)
find_package(SDL2_sound REQUIRED)
message(STATUS "INTERFACE_SDL2_SHARED: ${INTERFACE_SDL2_SHARED}")
message(STATUS "SDL2_SHARED: ${SDL2_SHARED}")
message(STATUS "VERSION: ${SDL2_sound_VERSION}")
message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_Sound_INCLUDE_DIRS: ${SDL2_Sound_INCLUDE_DIRS}")
message(STATUS "SDL2_Sound_INCLUDE_DIR: ${SDL2_Sound_INCLUDE_DIR}")
message(STATUS "SDL_Sound_INCLUDE_DIRS: ${SDL_Sound_INCLUDE_DIRS}")
message(STATUS "SDL_Sound_INCLUDE_DIR: ${SDL_Sound_INCLUDE_DIR}")
include(CMakePrintHelpers)

message(STATUS "DIRENT_INCLUDE_DIRS: ${DIRENT_INCLUDE_DIRS}")
message(STATUS "xxx: ${xxx}")

set(target gltron)
add_executable(${target} WIN32)
# target_sources(${target} PRIVATE gltron.rc)
# target_compile_options(${target} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)
# target_link_options(${target} PRIVATE $<$<CONFIG:Debug>:-fsanitize=address>)
target_link_libraries(${target} PRIVATE OpenGL::GL OpenGL::GLU)
target_link_libraries(${target} PRIVATE GLEW::GLEW)
target_link_libraries(${target} PRIVATE Ogg::ogg)
target_link_libraries(${target} PRIVATE FLAC::FLAC)
target_link_libraries(${target} PRIVATE ZLIB::ZLIB)
target_link_libraries(${target} PRIVATE PNG::PNG)
# Vorbis reference encoder and decoder, low-level API
target_link_libraries(${target} PRIVATE Vorbis::vorbis)
# Audio stream decoding and basic manipulation, high-level API
target_link_libraries(${target} PRIVATE Vorbis::vorbisfile)
# target_include_directories(${target} PRIVATE ${LUA_INCLUDE_DIR})
# target_link_libraries(${target} PRIVATE ${LUA_LIBRARIES})
target_link_libraries(${target}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${target} PRIVATE SDL2_sound::SDL2_sound)
if(WIN32)
target_link_libraries(${target} PRIVATE dirent)
endif()
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
target_compile_definitions(${target} PRIVATE
    # _CRT_SECURE_NO_WARNINGS
    # "GLEW_STATIC"
    # PATH_SEPARATOR='\\'
    # "PATH_SEPARATOR='\\'" # linux
    # "RC_NAME=gltron.ini"
    # "PREF_DIR='\\'"
    # "SNAP_DIR='\\'"
    LOCAL_DATA
    # WIN32
    _DEBUG
    # _WINDOWS
    HAVE_DEFINES_H
)
endif()
if(WIN32)
target_compile_definitions(${target} PRIVATE
    _CRT_SECURE_NO_WARNINGS
    # "GLEW_STATIC"
    # PATH_SEPARATOR='\\'
    # "PATH_SEPARATOR='\\'" # linux
    # "RC_NAME=gltron.ini"
    # "PREF_DIR='\\'"
    # "SNAP_DIR='\\'"
    LOCAL_DATA
    WIN32
    _DEBUG
    _WINDOWS
    HAVE_DEFINES_H
    # _CRT_SECURE_NO_WARNINGS
    # GLEW_STATIC
    # LOCAL_DATA
    # WIN32
    # _DEBUG
    # _WINDOWS
    _UNICODE
    UNICODE
)
endif()
# target_link_libraries(${target} PRIVATE libmikmod)
# target_link_libraries(${target} PRIVATE libmodplug)
# target_link_libraries(${target} PRIVATE ogg)

add_subdirectory(src)

add_subdirectory(GLtron)

# copy resources
set(resources
    art
    data
    levels
    music
    scripts
    sounds
)
foreach(resource IN LISTS resources)
    add_custom_command(TARGET ${target} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/Resources/${resource}
        $<TARGET_FILE_DIR:${target}>/${resource}
    )
endforeach()

cmake_print_properties(TARGETS SDL2_sound
PROPERTIES
    VERSION
    SOVERSION
    INTERFACE_SDL2_SHARED
    INTERFACE_INCLUDE_DIRECTORIES
    COMPATIBLE_INTERFACE_BOOL
    SDL2_SHARED
    DEFINE_SYMBOL
    SDL_SOUND_DLL_EXPORTS
    OUTPUT_NAME
)

cmake_print_properties(TARGETS gltron
PROPERTIES
    VERSION
    SOVERSION
    INTERFACE_SDL2_SHARED
    INTERFACE_INCLUDE_DIRECTORIES
    COMPATIBLE_INTERFACE_BOOL
    SDL2_SHARED
    DEFINE_SYMBOL
    SDL_SOUND_DLL_EXPORTS
    OUTPUT_NAME
)

cmake_print_properties(TARGETS SDL2::SDL2
PROPERTIES
    VERSION
    SOVERSION
    INTERFACE_SDL2_SHARED
    INTERFACE_INCLUDE_DIRECTORIES
    COMPATIBLE_INTERFACE_BOOL
    SDL2_SHARED
    DEFINE_SYMBOL
    SDL_SOUND_DLL_EXPORTS
    OUTPUT_NAME
)

# cmake_print_properties(TARGETS SDL2::SDL2-static
# PROPERTIES
#     VERSION
#     SOVERSION
#     INTERFACE_SDL2_SHARED
#     INTERFACE_INCLUDE_DIRECTORIES
#     COMPATIBLE_INTERFACE_BOOL
#     SDL2_SHARED
#     DEFINE_SYMBOL
#     SDL_SOUND_DLL_EXPORTS
#     OUTPUT_NAME
# )

# https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#genex:TARGET_RUNTIME_DLLS
if(WIN32)
set(target gltron)
add_custom_command(TARGET ${target} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:${target}> $<TARGET_RUNTIME_DLLS:${target}>
  COMMAND_EXPAND_LISTS
)
endif()
