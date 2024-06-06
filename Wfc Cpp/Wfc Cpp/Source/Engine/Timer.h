#pragma once

#include <SDL.h>

namespace Satellite
{
    class Timer
    {
    private:
        Uint32 start_ticks; // The clock time when the timer started
        Uint32 paused_ticks; // The ticks stored when the timer was paused

        bool is_paused;
        bool has_started;

    public:
        Timer();

        void Start();
        void Stop();
        void Pause();
        void Unpause();

        Uint32 GetTicks(); // Gets the timer's time

        bool IsStarted();
        bool IsPaused();
    };
}