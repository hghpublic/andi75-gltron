target_include_directories(${target}
PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/nebu/include
)

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
target_link_libraries(${target} PRIVATE lua5)


target_sources(${target} PRIVATE gltron.c)
