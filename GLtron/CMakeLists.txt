target_include_directories(${target}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nebu/include
)
# FIXME: replace with vcpkg: glew, libpng, lua5, zlib

add_subdirectory(audio)
add_subdirectory(base)
add_subdirectory(configuration)
add_subdirectory(filesystem)
add_subdirectory(game)
add_subdirectory(input)
add_subdirectory(lib3ds)
add_subdirectory(lua5)
add_subdirectory(nebu)
add_subdirectory(video)

target_link_libraries(${target} PRIVATE lib3ds)
if(false)
find_package(GLEW REQUIRED)
target_link_libraries(main PRIVATE GLEW::GLEW)
find_package(Ogg CONFIG REQUIRED)
target_link_libraries(main PRIVATE Ogg::ogg)
find_package(FLAC CONFIG REQUIRED)
target_link_libraries(main PRIVATE FLAC::FLAC)
find_package(ZLIB REQUIRED)
target_link_libraries(main PRIVATE ZLIB::ZLIB)
find_package(PNG REQUIRED)
target_link_libraries(main PRIVATE PNG::PNG)
# Vorbis reference encoder and decoder, low-level API
find_package(Vorbis CONFIG REQUIRED)
target_link_libraries(main PRIVATE Vorbis::vorbis)

# Audio stream decoding and basic manipulation, high-level API
find_package(Vorbis CONFIG REQUIRED)
target_link_libraries(main PRIVATE Vorbis::vorbisfile)

# Convenience API for setting up an encoding environment
find_package(Vorbis CONFIG REQUIRED)
target_link_libraries(main PRIVATE Vorbis::vorbisenc)
find_package(Lua REQUIRED)
target_include_directories(${target} PRIVATE ${LUA_INCLUDE_DIR})
target_link_libraries(${target} PRIVATE ${LUA_LIBRARIES})
endif()
target_link_libraries(${target} PRIVATE lua5)


target_sources(${target} PRIVATE gltron.c)
