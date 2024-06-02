#include "Timer.hpp"

namespace Quirk::Engine::Core::Utils
{
    void Timer::start()
    {
        m_start = std::chrono::high_resolution_clock::now();
    }

    void Timer::stop()
    {
        m_stop = std::chrono::high_resolution_clock::now();
        m_time = std::chrono::duration_cast<std::chrono::duration<double>>(m_stop - m_start);
    }
}