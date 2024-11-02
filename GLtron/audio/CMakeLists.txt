# project(audio
#     LANGUAGES C CXX
# )

# set(target audio)
# add_library(${target})
target_sources(${target} PRIVATE
    sound.c
    sound_glue.cpp
    # sound_glue_stubs.cpp
    # sound_stubs.c
)
# target_include_directories(${target}
# PRIVATE
#     ${CMAKE_CURRENT_LIST_DIR}/../include
#     ${CMAKE_CURRENT_LIST_DIR}/../nebu/include
#     ${LUA_INCLUDE_DIR}
#     ${SDL2_INCLUDE_DIRS}
# )
# https://wiki.libsdl.org/SDL2/README/cmake
# message(STATUS "SDL2_INCLUDE_DIRS: ${SDL2_INCLUDE_DIRS}")
# message(STATUS "SDL2_INCLUDE_DIR: ${SDL2_INCLUDE_DIR}")
# message(STATUS "SDL2_LIBRARIES: ${SDL2_LIBRARIES}")
# message(STATUS "SDL2_FOUND: ${SDL2_FOUND}")
# message(STATUS "SDL2_EXEC_PREFIX: ${SDL2_EXEC_PREFIX}")
# message(STATUS "SDL2_LIBDIR: ${SDL2_LIBDIR}")

# https://cmake.org/cmake/help/latest/module/FindSDL_sound.html
# message(STATUS "SDL_SOUND_INCLUDE_DIR: ${SDL_SOUND_INCLUDE_DIR}")
# message(STATUS "SDL_SOUND_FOUND: ${SDL_SOUND_FOUND}")
# message(STATUS "SDL_SOUND_LIBRARIES: ${SDL_SOUND_LIBRARIES}")
# message(STATUS "SDL_SOUND_EXTRAS: ${SDL_SOUND_EXTRAS}")
# message(STATUS "SDL_SOUND_VERSION_STRING: ${SDL_SOUND_VERSION_STRING}")
# message(STATUS "SDL_SOUND_LIBRARY: ${SDL_SOUND_LIBRARY}")
# message(STATUS "SDL_SOUND_LIBRARIES: ${SDL_SOUND_LIBRARIES}")

# SDL2_sound::SDL2_sound
# SDL2_sound::SDL2_sound-static
# message(STATUS "SDLSOUND_VERSION: ${SDLSOUND_VERSION}")
# message(STATUS "SDL2_sound_SDL2_sound_FOUND: ${SDL2_sound_SDL2_sound_FOUND}")
# message(STATUS "SDL2_sound_SDL2_sound-static_FOUND: ${SDL2_sound_SDL2_sound-static_FOUND}")
# message(STATUS "xxx: ${xxx}")
# message(STATUS "xxx: ${xxx}")
# message(STATUS "xxx: ${xxx}")
# message(STATUS "xxx: ${xxx}")
