#include "Timer.h"

namespace Satellite
{
    Timer::Timer()
    {
        start_ticks = 0;
        paused_ticks = 0;

        is_paused = false;
        has_started = false;
    }

    void Timer::Start()
    {
        has_started = true;
        is_paused = false;

        start_ticks = SDL_GetTicks();
        paused_ticks = 0;
    }

    void Timer::Stop()
    {
        has_started = false;
        is_paused = true;

        start_ticks = 0;
        paused_ticks = 0;
    }

    void Timer::Pause()
    {
        if (has_started && !is_paused)
        {
            is_paused = true;

            // Calculate the paused ticks

            paused_ticks = SDL_GetTicks() - start_ticks;
            start_ticks = 0;
        }
    }

    void Timer::Unpause()
    {
        if (has_started && is_paused)
        {
            is_paused = false;

            start_ticks = SDL_GetTicks() - paused_ticks;

            paused_ticks = 0;
        }
    }

    Uint32 Timer::GetTicks()
    {
        if (has_started)
        {
            if (is_paused)
            {
                return paused_ticks;
            }
            else
            {
                return SDL_GetTicks() - start_ticks;
            }
        }
    }

    bool Timer::IsStarted() { return has_started; }

    bool Timer::IsPaused() { return is_paused && has_started; }
}