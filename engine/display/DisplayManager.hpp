#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "DisplayWindow.hpp"
#include "../core/Utils.hpp"

namespace Quirk::Engine::Display
{
    // Probably only going to have one display, but this is here for future proofing
    enum class DisplayTypes
    {
        Default,
    };

    class DisplayManager
    {
    public:
        DisplayManager();
        ~DisplayManager();

        DisplayWindow getWindow(DisplayTypes type) { return *m_windows[type]; }
        void windowTick(DisplayTypes type);
        void setCurrentContext(DisplayTypes type) { return glfwMakeContextCurrent(m_windows[type]->handle); }
        bool windowsShouldClose();

    private:
        void initGlfw();
        void initGlad();
        void createDefaultWindow();

    private:
        std::unordered_map<DisplayTypes, std::shared_ptr<DisplayWindow>> m_windows;
    };
}
