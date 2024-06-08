#pragma once

#include <unordered_map>
#include <string>
#include <memory>

#include "../core/utils/Utils.hpp"
#include "../core/utils/ApplicationSettings.hpp"

#include "../core/eventSystem/EventBus.hpp"
#include "../core/eventSystem/events/KeyPressEvent.hpp"
#include "../core/eventSystem/events/WindowResizeEvent.hpp"

#include "DisplayWindow.hpp"

using namespace Quirk::Engine::Core::Utils;
using namespace Quirk::Engine::Core::EventSystem::Events;
using namespace Quirk::Engine::Core::EventSystem;

using AppSettings = Quirk::Engine::Core::Utils::ApplicationSettings;

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
        ~DisplayManager();

        static void init();
        static void initWindows();
        static DisplayWindow getWindow(DisplayTypes type) { return *m_windows[type]; }
        static void tick(DisplayTypes type, double tickSpeed);
        static void setCurrentContext(DisplayTypes type) { return glfwMakeContextCurrent(m_windows[type]->handle); }
        static bool windowsShouldClose();
        static void handleWindowInput(const KeyPressEvent& event);



    private:
        static void initGlfw(const SettingsObject& settings);
        static void createDefaultWindow(const SettingsObject& settings);

    private:
        inline static std::unordered_map<DisplayTypes, std::unique_ptr<DisplayWindow>> m_windows{};
    };
}
