project(lib3ds)

set(target lib3ds)
add_library(${target} STATIC)
target_sources(${target} PRIVATE
    atmosphere.c
    atmosphere.h

    background.c
    background.h

    camera.c
    camera.h

    chunk.c
    chunk.h

    chunktable.h
    config.h

    ease.c
    ease.h

    file.c
    file.h

    io.c
    io.h

    light.c
    light.h

    material.c
    material.h

    matrix.c
    matrix.h

    mesh.c
    mesh.h

    node.c
    node.h

    quat.c
    quat.h

    shadow.c
    shadow.h

    tcb.c
    tcb.h

    tracks.c
    tracks.h

    vector.c
    vector.h

    viewport.c
    viewport.h

    float.c

    float3ds.h
    types.h
)
target_include_directories(${target} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)
