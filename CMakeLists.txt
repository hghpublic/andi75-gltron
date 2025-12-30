cmake_minimum_required(VERSION 3.30)



message(STATUS "DOTNET_CLI_UI_LANGUAGE: $ENV{DOTNET_CLI_UI_LANGUAGE}")

# https://sourceforge.net/projects/gltron/
project(gltron
    VERSION 0.70
    DESCRIPTION "gltron was inspired by the film tron - actually, more by all the games that where inspired by the film tron :-)"
    HOMEPAGE_URL "http://www.gltron.org/"
    LANGUAGES C CXX
)

# if using valgrind, set BUILD_WITH_ASAN to OFF
option(BUILD_WITH_ASAN "Build with ASAN" ON)
option(USE_SDL2_SOUND "Use SDL2_sound library for additional sound formats" OFF)
# sound in devcontainer only seems to work with SDL2 from apt
option(USE_APT_SDL2 "Use SDL2 from apt repository on Linux" ON)
option(USE_VCPKG_SDL2 "Use SDL2 from vcpkg package manager" OFF)

# fetch content

include(FetchContent) # once in the project to include the module

# dirent
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
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

if(USE_SDL2_SOUND)
# SDL_sound
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
# https://github.com/icculus/SDL_sound
FetchContent_Declare(SDL_sound
    GIT_REPOSITORY https://github.com/icculus/SDL_sound.git
    GIT_TAG        e731e61abdc274a18f1395c1ad999a9e8313b638 # 2.02
    OVERRIDE_FIND_PACKAGE
)
else()
FetchContent_Declare(SDL_sound
    GIT_REPOSITORY https://github.com/hghpublic/icculus-SDL_sound.git
    GIT_TAG        SDL_sound/2.0.3/gltron
    OVERRIDE_FIND_PACKAGE
)
endif()
FetchContent_MakeAvailable(SDL_sound)
endif()

# dirent
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
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

# pkgconfig

find_package(PkgConfig REQUIRED)
pkg_check_modules(libmikmod REQUIRED IMPORTED_TARGET libmikmod)
pkg_check_modules(libmodplug REQUIRED IMPORTED_TARGET libmodplug)
pkg_check_modules(ogg REQUIRED IMPORTED_TARGET ogg)

# find packages

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
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
if(USE_SDL2_SOUND)
find_package(SDL_sound REQUIRED)
endif()
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
find_package(dirent REQUIRED)
message(STATUS "DIRENT_INCLUDE_DIRS: ${DIRENT_INCLUDE_DIRS}")
message(STATUS "xxx: ${xxx}")
endif()
find_package(OpenGL REQUIRED)

# target executable GLtronApp

set(target GLtronApp)
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
add_executable(${target} WIN32)
else()
add_executable(${target})
endif()
target_sources(${target} PRIVATE
    dev/src/GLtron/nebu_Log.cpp
)
if(BUILD_WITH_ASAN)
    target_compile_options(${target} PRIVATE -fsanitize=address)
    target_link_options(${target} PRIVATE -fsanitize=address)
endif()
target_compile_features(${target} PRIVATE cxx_std_26 c_std_23)
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
target_link_libraries(${target} PRIVATE OpenGL::GL OpenGL::GLU)
if(USE_APT_SDL2)
target_link_libraries(${target} PRIVATE SDL2::SDL2)
target_link_libraries(${target} PRIVATE SDL2_mixer::SDL2_mixer)
elseif(USE_VCPKG_SDL2)
target_link_libraries(${target}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${target} PRIVATE
    $<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,
        SDL2_mixer::SDL2_mixer,
        SDL2_mixer::SDL2_mixer-static>)
endif()
if(USE_SDL2_SOUND)
target_link_libraries(${target} PRIVATE SDL2_sound::SDL2_sound)
endif()
if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
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
else()
target_compile_definitions(${target} PRIVATE
    LOCAL_DATA
    _DEBUG
    HAVE_DEFINES_H
)
endif()
# target_link_libraries(${target} PRIVATE libmikmod)
# target_link_libraries(${target} PRIVATE libmodplug)
# target_link_libraries(${target} PRIVATE ogg)

add_subdirectory(dev/src/GLtron)
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


# valgrind target

add_custom_target(valgrind
    COMMAND valgrind
        --leak-check=full
        --show-leak-kinds=all
        --track-origins=yes
        -s --suppressions=$ENV{DEV_ROOT}/valgrind/gltron.valgrind.supp
        --gen-suppressions=all
        --log-file=$ENV{DEV_ROOT}/valgrind/logs/memcheck.log
        $<TARGET_FILE:${target}>
    DEPENDS ${target}
    WORKING_DIRECTORY $<TARGET_FILE_DIR:${target}>
    COMMENT "Running GLtronApp with valgrind"
)

option(BUILD_SDLSOUND_EXAMPLES "Build SDL_sound example programs" OFF)
option(BUILD_SDLKITCHENSINK_EXAMPLES "Build SDL_kitchensink example programs" OFF)

if(BUILD_SDLSOUND_EXAMPLES)
    add_subdirectory(src/SDL_sound/examples)
endif()
if(BUILD_SDLKITCHENSINK_EXAMPLES)
    add_subdirectory(src/SDL_kitchensink/examples)
endif()
