// sound_glue.cpp
// Glue code for SDL2_mixer audio backend

#include <format>
#include <iostream>
#include <print>
#include <source_location>
#include <string_view>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

namespace
{
    void log(const std::string_view message,
             const std::source_location location =
                 std::source_location::current())
    {
        std::println(std::clog, "file: {}({}:{}) `{}`: {}",
                     location.file_name(),
                     location.line(),
                     location.column(),
                     location.function_name(),
                     message);
    }

    static void output_decoders(void)
    {
        log("not implemented");
    } // output_decoders

    static constexpr float TURNLENGTH{250.0f};

    // static constexpr const char *MUSIC_GAME_CRASH = "data/game_crash.wav";
    // static constexpr const char *MUSIC_GAME_ENGINE = "data/game_engine.wav";
    // static constexpr const char *MUSIC_GAME_RECOGNIZER = "data/game_recognizer.wav";
    // static constexpr const char *MUSIC_SONG_REVENGE_OF_CATS = "music/song_revenge_of_cats.mp3";

    // enum SoundEffects : int
    // {
    //     SOUND_EFFECT_ENGINE = 0,
    //     SOUND_EFFECT_CRASH = 1,
    //     SOUND_EFFECT_RECOGNIZER = 2
    // };

    // enum MusicTracks : int
    // {
    //     MUSIC_TRACK_REVENGE_OF_CATS = 0
    // };

    std::array<Mix_Chunk *, 3> samples{nullptr};
    Mix_Music *music{nullptr};

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

extern "C"
{
    void Audio_EnableEngine(void)
    {
        log("not implemented");
    } // Audio_EnableEngine

    void Audio_DisableEngine(void)
    {
        log("not implemented");
    } // Audio_DisableEngine

    void Audio_Idle(void)
    {
        // called continuously
        // log("not implemented");
    } // Audio_Idle

    void Audio_CrashPlayer(int player)
    {
        log(std::format("not implemented. player={}", player));
    } // Audio_CrashPlayer

    void Audio_Init(void)
    {
        // log("not implemented");
        log("Initializing audio");

        int flags = MIX_INIT_MP3;
        int result = Mix_Init(flags);
        if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == MIX_ERROR)
        {
            print_sdl_error("SDL2_mixer could not be initialized!");
        }
    } // Audio_Init

    void Audio_Start(void)
    {
        log("not implemented");
        // log("Starting audio");
    } // Audio_Start

    void Audio_Quit(void)
    {
        // log("not implemented");
        log("Quitting audio");

        for (auto &sample : samples)
        {
            Mix_FreeChunk(sample);
            sample = nullptr;
        }

        Mix_FreeMusic(music);

        Mix_CloseAudio();

    } // Audio_Quit

    void Audio_LoadMusic(char *name)
    {
        // log(std::format("not implemented - name={}", name));
        log(std::format("Loading music - name={}", name));

        music = Mix_LoadMUS(name);
        Mix_PlayMusic(music, 1);
    } // Audio_LoadMusic

    void Audio_PlayMusic(void)
    {
        // log("not implemented");
        log("Playing music");

        // Mix_PlayMusic(clapnsnare4, 1);
        Mix_Resume(MIX_RESUME_ALL_PAUSED_CHANNELS);
    } // Audio_PlayMusic

    void Audio_StopMusic(void)
    {
        log("not implemented");

        // if (Mix_Paused(MIX_QUERY_ALL_CHANNELS))
        //     Mix_Resume(MIX_RESUME_ALL_PAUSED_CHANNELS);
        // else
        //     Mix_Pause(MIX_PAUSE_ALL_CHANNELS);
    } // Audio_StopMusic

    void Audio_SetMusicVolume(float volume)
    {
        // log(std::format("not implemented - volume={}", volume));
        log(std::format("Set music volume - volume={}", volume));
        int mix_volume = static_cast<int>(volume * MIX_MAX_VOLUME);

        for (int i = 0; i < MIX_CHANNELS; ++i)
        {
            Mix_Volume(i, mix_volume);
        }
    } // Audio_SetMusicVolume

    void Audio_SetFxVolume(float volume)
    {
        log(std::format("not implemented - volume={}", volume));
    } // Audio_SetFxVolume

    void Audio_StartEngine(int iPlayer)
    {
        log(std::format("not implemented - iPlayer={}", iPlayer));
    } // Audio_StartEngine

    void Audio_StopEngine(int iPlayer)
    {
        log(std::format("not implemented - iPlayer={}", iPlayer));
    } // Audio_StopEngine

    void Audio_ResetData(void)
    {
        log("not implemented");

    } // Audio_ResetData

    void Audio_UnloadPlayers(void)
    {
        log("not implemented");
    } // Audio_UnloadPlayers

    void Audio_LoadPlayers(void)
    {
        log("not implemented");
    } // Audio_LoadPlayers

    void Audio_LoadSample(char *name, int number)
    {
        // log(std::format("not implemented - name={}, number={}", name, number));
        log(std::format("Loading sample - name={}, number={}", name, number));

        samples[number] = Mix_LoadWAV(name);

        Mix_PlayChannel(MIX_PLAY_FIRST_FREE_CHANNEL, samples[number], 0);
    } // Audio_LoadSample
}
