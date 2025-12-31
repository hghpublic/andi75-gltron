#include <format>
#include <iostream>
#include <print>
#include <source_location>
#include <string_view>

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
        log("not implemented");
    } // Audio_Init

    void Audio_Start(void)
    {
        log("not implemented");

    } // Audio_Start

    void Audio_Quit(void)
    {
        log("not implemented");

    } // Audio_Quit

    void Audio_LoadMusic(char *name)
    {
        log(std::format("not implemented - name={}", name));

    } // Audio_LoadMusic

    void Audio_PlayMusic(void)
    {
        log("not implemented");

    } // Audio_PlayMusic

    void Audio_StopMusic(void)
    {
        log("not implemented");
    } // Audio_StopMusic

    void Audio_SetMusicVolume(float volume)
    {
        log(std::format("not implemented - volume={}", volume));
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
        log(std::format("not implemented - name={}, number={}", name, number));
    } // Audio_LoadSample
}
