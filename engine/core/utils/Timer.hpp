#pragma once
#include <chrono>
#include <iostream>

namespace Quirk::Engine::Core::Utils
{
    class Timer
    {
    public:
        static void start();
        static double stop();

    private:
        inline static std::chrono::high_resolution_clock::time_point m_start{};
        inline static std::chrono::high_resolution_clock::time_point m_stop{};
        inline static std::chrono::duration<double> m_time{};
    };
}
