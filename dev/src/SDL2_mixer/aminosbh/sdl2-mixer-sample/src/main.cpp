/*
 * Copyright (c) 2018, 2019 Amine Ben Hassouna <amine.benhassouna@gmail.com>
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any
 * person obtaining a copy of this software and associated
 * documentation files (the "Software"), to deal in the
 * Software without restriction, including without
 * limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software
 * is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice
 * shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
 * ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
 * TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
 * SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR
 * IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include <print>

namespace
{
    static constexpr auto MAX = [](auto X, auto Y)
    {
        return (X > Y) ? X : Y;
    };
    static constexpr auto MIN = [](auto X, auto Y)
    {
        return (X < Y) ? X : Y;
    };

    static constexpr int SCREEN_WIDTH{800};
    static constexpr int SCREEN_HEIGHT{600};

    static constexpr const char *WAVES_SOUND = "assets/waves-at-baltic-sea-shore/waves-at-baltic-sea-shore.wav";

    static constexpr const char *CLAP_SOUND = "assets/claps-and-snares/clap.ogg";
    static constexpr const char *SNARE_SOUND = "assets/claps-and-snares/snare.ogg";
    static constexpr const char *TECHNO_CLAP_SNARE_SOUND = "assets/claps-and-snares/techno-clap-snare.ogg";
    static constexpr const char *REVERB_SNARE_SOUND = "assets/claps-and-snares/dubstep-reverb-snare.ogg";

    static constexpr auto print_sdl_error = [](const char *message)
    {
        std::print("{}\nSDL_Error: {}\n", message, SDL_GetError());
    };

    static constexpr int MIX_ERROR{-1};
    static constexpr int MIX_LOOP_INFINITE{-1};
    static constexpr int MIX_PAUSE_ALL_CHANNELS{-1};
    static constexpr int MIX_RESUME_ALL_PAUSED_CHANNELS{-1};
    static constexpr int MIX_PLAY_FIRST_FREE_CHANNEL{-1};
    static constexpr int MIX_QUERY_ALL_CHANNELS{-1};
} // namespace

int main([[maybe_unused]] int argc, [[maybe_unused]] char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        print_sdl_error("SDL could not be initialized!");
        return EXIT_FAILURE;
    }

    if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == MIX_ERROR)
    {
        print_sdl_error("SDL2_mixer could not be initialized!");
        return EXIT_FAILURE;
    }

    SDL_Window *window = SDL_CreateWindow("SDL2 audio sample (Press SPACE to pause/play)",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (!window)
    {
        print_sdl_error("Window could not be created!");
    }
    else
    {
        SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!renderer)
        {
            print_sdl_error("Renderer could not be created!");
        }
        else
        {
            // Load .WAV sound
            Mix_Chunk *waves = Mix_LoadWAV(WAVES_SOUND);
            if (!waves)
            {
                std::print(".WAV sound '{}' could not be loaded!\nSDL_Error: {}\n",
                           WAVES_SOUND, SDL_GetError());
                return EXIT_FAILURE;
            }

            Mix_Music *clapnsnare1 = Mix_LoadMUS(CLAP_SOUND);
            Mix_Music *clapnsnare2 = Mix_LoadMUS(SNARE_SOUND);
            Mix_Music *clapnsnare3 = Mix_LoadMUS(TECHNO_CLAP_SNARE_SOUND);
            Mix_Music *clapnsnare4 = Mix_LoadMUS(REVERB_SNARE_SOUND);
            if (!clapnsnare1 || !clapnsnare2 || !clapnsnare3 || !clapnsnare4)
            {
                print_sdl_error("One of the .OGG sounds could not be loaded!\n");
                return EXIT_FAILURE;
            }

            if (Mix_PlayChannel(MIX_PLAY_FIRST_FREE_CHANNEL, waves, 0) == MIX_ERROR)
            {
                print_sdl_error("Waves sound could not be played!");
                Mix_FreeChunk(waves);
                return EXIT_FAILURE;
            }

            SDL_Rect squareRect;

            squareRect.w = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;
            squareRect.h = MIN(SCREEN_WIDTH, SCREEN_HEIGHT) / 2;

            squareRect.x = SCREEN_WIDTH / 2 - squareRect.w / 2;
            squareRect.y = SCREEN_HEIGHT / 2 - squareRect.h / 2;

            SDL_Rect pauseRect1, pauseRect2;
            pauseRect1.h = squareRect.h / 2;
            pauseRect1.w = 40;
            pauseRect1.x = squareRect.x + (squareRect.w - pauseRect1.w * 3) / 2;
            pauseRect1.y = squareRect.y + squareRect.h / 4;
            pauseRect2 = pauseRect1;
            pauseRect2.x += pauseRect1.w * 2;

            // handle events

            bool quit = false;

            static auto handle_events = [&]()
            {
                SDL_Event e;

                SDL_WaitEvent(&e);

                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }
                else if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_SPACE:
                        if (Mix_Paused(MIX_QUERY_ALL_CHANNELS))
                            Mix_Resume(MIX_RESUME_ALL_PAUSED_CHANNELS);
                        else
                            Mix_Pause(MIX_PAUSE_ALL_CHANNELS);
                        break;

                    case SDLK_RIGHT:
                        if (Mix_PlayMusic(clapnsnare1, 1) == MIX_ERROR)
                        {
                            print_sdl_error(".OGG sound could not be played!");
                        }
                        break;

                    case SDLK_LEFT:
                        if (Mix_PlayMusic(clapnsnare2, 1) == MIX_ERROR)
                        {
                            print_sdl_error(".OGG sound could not be played!");
                        }
                        break;

                    case SDLK_UP:
                        if (Mix_PlayMusic(clapnsnare3, 1) == MIX_ERROR)
                        {
                            print_sdl_error(".OGG sound could not be played!");
                        }
                        break;

                    case SDLK_DOWN:
                        if (Mix_PlayMusic(clapnsnare4, 1) == MIX_ERROR)
                        {
                            print_sdl_error(".OGG sound could not be played!");
                        }
                        break;
                    }
                }
            };

            static auto draw = [&]()
            {
                SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                SDL_RenderClear(renderer);

                SDL_SetRenderDrawColor(renderer, 0x19, 0x71, 0xA9, 0xFF);

                SDL_RenderFillRect(renderer, &squareRect);

                if (Mix_Paused(MIX_QUERY_ALL_CHANNELS))
                {
                    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

                    SDL_RenderFillRect(renderer, &pauseRect1);
                    SDL_RenderFillRect(renderer, &pauseRect2);
                }

                SDL_RenderPresent(renderer);
            };

            // update loop

            while (!quit)
            {
                handle_events();

                draw();
            }

            // cleanup

            Mix_FreeChunk(waves);

            Mix_FreeMusic(clapnsnare1);
            Mix_FreeMusic(clapnsnare2);
            Mix_FreeMusic(clapnsnare3);
            Mix_FreeMusic(clapnsnare4);

            SDL_DestroyRenderer(renderer);
        }

        SDL_DestroyWindow(window);
    }

    Mix_CloseAudio();

    SDL_Quit();

    return EXIT_SUCCESS;
}
