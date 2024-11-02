project(nebu)

set(target nebu)

add_library(${target} STATIC)

add_subdirectory(audio)
add_subdirectory(base)
add_subdirectory(filesystem)
add_subdirectory(input)
add_subdirectory(scripting)
add_subdirectory(video)

target_compile_definitions(${target} PRIVATE HAVE_DEFINES_H)
target_include_directories(${target} PUBLIC ${SDL2_INCLUDE_DIRS})
target_include_directories(${target} PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(${target} PUBLIC ${DEFINES_H_INCLUDE_DIR})
target_link_libraries(${target} PRIVATE lua5)
target_link_libraries(${target} PRIVATE lib3ds)
target_link_libraries(${target} PRIVATE SDL2_sound::SDL2_sound)
target_link_libraries(${target} PRIVATE PNG::PNG)
