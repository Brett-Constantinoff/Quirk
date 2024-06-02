#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "DisplayWindow.hpp"
#include "../core/Utils.hpp"
#include "../core/ApplicationSettings.hpp"

using namespace Quirk::Engine::Core;

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
        DisplayManager() = default;
        ~DisplayManager();

        void init();
        void initWindows();
        DisplayWindow getWindow(DisplayTypes type) { return *m_windows[type]; }
        void tick(DisplayTypes type, double tickSpeed);
        void setCurrentContext(DisplayTypes type) { return glfwMakeContextCurrent(m_windows[type]->handle); }
        bool windowsShouldClose();

    private:
        void initGlfw(const SettingsObject& settings);
        void createDefaultWindow(const SettingsObject& settings);

    private:
        std::unordered_map<DisplayTypes, std::shared_ptr<DisplayWindow>> m_windows;
    };
}
