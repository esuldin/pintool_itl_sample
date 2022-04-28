#include "time.h"

#include <Windows.h>
#include <profileapi.h>


namespace pintool
{
namespace time
{

timer::timer()
    : start_timestamp(ticks())
{}

timer::ticks_type timer::ticks() const
{
#ifdef _WIN32
    LARGE_INTEGER timestamp;
    if (QueryPerformanceCounter(&timestamp)) {
        return static_cast<ticks_type>(timestamp.QuadPart);
    }
#endif
    return 0;
}

timer::ticks_type timer::frequency() const
{
#ifdef _WIN32
    LARGE_INTEGER frequency;
    if (QueryPerformanceFrequency(&frequency)) {
        return static_cast<ticks_type>(frequency.QuadPart);
    }
#endif

    return 0;
}

timer::ticks_type timer::elapsed() const
{
    const ticks_type current_timestamp = ticks();
    const ticks_type freq = frequency();

    if (freq) {
        return static_cast<ticks_type>((current_timestamp - start_timestamp) * 10e6 / freq);
    }

    return 0;
}

} // namespace time
} // namespace pintool