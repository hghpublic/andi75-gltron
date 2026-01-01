#include <print>
#include <cstdarg>

namespace
{
    // Source - https://stackoverflow.com/a
    // Posted by Guillaume.P
    // Retrieved 2026-01-01, License - CC BY-SA 4.0

    template <class... Args>
    void foo(const char *format, Args... args)
    {
        printf(format, args...);
    }

    template <class... Args>
    void nebu_Log2(const char *format, Args... args)
    {
        std::print(format, args...);
    }
} // anonymous namespace

extern "C"
{
    void nebu_Log(const char *format, ...)
    {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
}