// main.c
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // Initialize SDL and SDL_mixer (simplified for example)
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! %s\n", Mix_GetError());
        return EXIT_FAILURE;
    }

    printf("--- Chunk Decoders ---\n");
    int num_chunks = Mix_GetNumChunkDecoders();
    for (int i = 0; i < num_chunks; i++)
    {
        printf("%s\n", Mix_GetChunkDecoder(i));
    }

    printf("\n--- Music Decoders ---\n");
    int num_music = Mix_GetNumMusicDecoders();
    for (int i = 0; i < num_music; i++)
    {
        printf("%s\n", Mix_GetMusicDecoder(i));
    }

    Mix_CloseAudio();
    return EXIT_SUCCESS;
}
