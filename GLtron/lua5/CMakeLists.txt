set(target lua5)
add_library(${target} SHARED)
target_sources(${target} PRIVATE
    
    lapi.c
    lapi.h
    
    lcode.c
    lcode.h
    
    ldebug.c
    ldebug.h
    
    ldo.c
    ldo.h
    
    ldump.c
    
    lfunc.c
    lfunc.h
    
    lgc.c
    lgc.h
    
    llex.c
    llex.h
    
    llimits.h
    
    lmem.c
    lmem.h
    
    lobject.c
    lobject.h
    
    lopcodes.c
    lopcodes.h

    lparser.c
    lparser.h
    
    lstate.c
    lstate.h
    
    lstring.c
    lstring.h
    
    ltable.c
    ltable.h
    
    # ltests.c
    
    ltm.c
    ltm.h
    
    lundump.c
    lundump.h
    
    lvm.c
    lvm.h
    
    lzio.c
    lzio.h
)
target_include_directories(${target}
PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/include
INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}/include
)

add_subdirectory(lib)
