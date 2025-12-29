cmake_minimum_required(VERSION 3.30)

project(SDL_kitchensink-examples C)

# find_package(SDL2 CONFIG REQUIRED)
# find_package(ffmpeg COMPONENTS avcodec avformat avutil swscale swresample)
# pkg_check_modules(SDL_kitchensink REQUIRED IMPORTED_TARGET SDL_kitchensink)
# SDL_kitchensink
# https://github.com/katajakasa/SDL_kitchensink
include(FetchContent)
FetchContent_Declare(SDL_kitchensink
    GIT_REPOSITORY https://github.com/katajakasa/SDL_kitchensink.git
    GIT_TAG        master
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SDL_kitchensink)

set(targets
    example_audio
    example_complex
    example_custom
    example_rawdump
    example_rwops
    example_simple
)

foreach(target IN LISTS targets)
add_executable(${target})
target_compile_features(${target} PRIVATE c_std_23)
target_sources(${target} PRIVATE ${target}.c)
target_link_libraries(${target} PRIVATE SDL_kitchensink)
target_link_libraries(${target}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
if(ffmpeg_FOUND)
    target_link_libraries(${target} PRIVATE ffmpeg::avcodec ffmpeg::avformat ffmpeg::avutil ffmpeg::swscale ffmpeg::swresample)
endif()
set_target_properties(${target} PROPERTIES
    FOLDER "SDL_kitchensink Examples"
)    
endforeach()
