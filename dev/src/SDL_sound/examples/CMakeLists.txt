cmake_minimum_required(VERSION 3.30)

project(SDL_sound-examples C)

find_package(SDL2 CONFIG REQUIRED)

# SDL_sound
include(FetchContent)
FetchContent_Declare(SDL_sound
    GIT_REPOSITORY https://github.com/hghpublic/icculus-SDL_sound.git
    GIT_TAG        SDL_sound/2.0.3/gltron
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SDL_sound)

# playsound

set(target playsound)
add_executable(${target})
target_compile_features(${target} PRIVATE c_std_23)
target_sources(${target} PRIVATE playsound.c)
target_link_libraries(${target}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${target} PRIVATE SDL2_sound::SDL2_sound)
# assuming assert.h, signal.h and setbuf() being available universally
target_compile_definitions(${target} PRIVATE "HAVE_SETBUF")
target_compile_definitions(${target} PRIVATE "HAVE_ASSERT_H")
target_compile_definitions(${target} PRIVATE "HAVE_SIGNAL_H")
set_target_properties(${target} PROPERTIES
    FOLDER "SDL_sound Examples"
)

# playsound_simple

set(target playsound_simple)
add_executable(${target} playsound_simple.c)
target_compile_features(${target} PRIVATE c_std_23)
target_link_libraries(${target}
    PRIVATE
    $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
    $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
target_link_libraries(${target} PRIVATE SDL2_sound::SDL2_sound)
set_target_properties(${target} PROPERTIES
    FOLDER "SDL_sound Examples"
)
