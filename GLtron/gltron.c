/*
  gltron
  Copyright (C) 1999 by Andreas Umbach <marvin@dataway.ch>
*/

#include "base/nebu_system.h" // includes main

// #include "base/nebu_debug_memory.h"
// #include "base/nebu_assert.h"

#include "game/init.h"
#include "filesystem/path.h"
#include "base/util.h"

#if defined(WIN32)
#include <direct.h>
#include <errno.h>
#include <SDL.h>
void chdirToBasePath()
{
    const char* basePath = SDL_GetBasePath();
    if (_chdir(basePath))
    {
        switch (errno)
        {
        case ENOENT:
            printf("Unable to locate the directory: %s\n", basePath);
            break;
        case EINVAL:
            printf("Invalid buffer.\n");
            break;
        default:
            printf("Unknown error.\n");
        }
    }
}
#endif

int main(int argc, char *argv[] ) {
#if defined(WIN32)
    chdirToBasePath();
#endif
	// nebu_debug_memory_CheckLeaksOnExit();
	// nebu_assert_config(NEBU_ASSERT_PRINT_STDERR);
	initSubsystems(argc, (const char**) argv);
	runScript(PATH_SCRIPTS, "main.lua");
	exitSubsystems();
	return 0;
}







