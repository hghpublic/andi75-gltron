// main.c
// Simplified code from chromium-bsu/src/AudioSDLMixer.cpp
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <string.h>

int main(int argc, char *argv[])
{
    char file[256] = {0};
    const char *workspace_root = getenv("WORKSPACE_ROOT");
    strncpy(file, workspace_root, sizeof(file) - 1);
    strncat(file, "/Resources/music/song_revenge_of_cats.mp3", sizeof(file) - strlen(file) - 1);

    printf("Playing music from: %s\n", file);

    int flags = MIX_INIT_MP3;
    int result = Mix_Init(flags);
    Mix_OpenAudio(22050, AUDIO_S16, 2, 512);
    Mix_Music *music = Mix_LoadMUS(file);

    atexit(Mix_CloseAudio);

    int value = 0x0f; // volume level from 0 to 128
    for (int i = 1; i < MIX_CHANNELS; i++)
    {
        Mix_Volume(i, (int)(MIX_MAX_VOLUME * value));
    }
    Mix_Volume(0, (int)(MIX_MAX_VOLUME * value));

    Mix_PlayMusic(music, 1);

    SDL_Delay(5000); // wait for 5 seconds to let the music play

    Mix_FreeMusic(music);
    
    return EXIT_SUCCESS;
}
