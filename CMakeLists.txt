cmake_minimum_required(VERSION 3.30)



message(STATUS "DOTNET_CLI_UI_LANGUAGE: $ENV{DOTNET_CLI_UI_LANGUAGE}")

# https://sourceforge.net/projects/gltron/
project(gltron
    VERSION 0.70
    DESCRIPTION "gltron was inspired by the film tron - actually, more by all the games that where inspired by the film tron :-)"
    HOMEPAGE_URL "http://www.gltron.org/"
    LANGUAGES C CXX
)

include(FetchContent) # once in the project to include the module

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

# SDL_sound
# https://github.com/icculus/SDL_sound
FetchContent_Declare(SDL_sound
    GIT_REPOSITORY https://github.com/icculus/SDL_sound.git
    GIT_TAG        e731e61abdc274a18f1395c1ad999a9e8313b638 # 2.02
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SDL_sound)

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
find_package(SDL_sound REQUIRED)
find_package(dirent REQUIRED)

message(STATUS "DIRENT_INCLUDE_DIRS: ${DIRENT_INCLUDE_DIRS}")
message(STATUS "xxx: ${xxx}")


set(target gltron)
add_executable(${target} WIN32)
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
target_link_libraries(${target} PRIVATE dirent)
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
)
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
