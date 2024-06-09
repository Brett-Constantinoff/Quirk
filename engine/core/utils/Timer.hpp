#pragma once

#include <chrono>
#include <iostream>

namespace Quirk::Engine::Core::Utils
{
    class Timer
    {
    public:
        Timer() = default;
        ~Timer() = default;

        void start();
        double stop();

    private:
        std::chrono::high_resolution_clock::time_point m_start{};
        std::chrono::high_resolution_clock::time_point m_stop{};
        std::chrono::duration<double> m_time{};
    };
}
