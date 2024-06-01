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
        /// <summary>
        /// Creates a display manager with a default window.
        /// </summary>
        DisplayManager();

        /// <summary>
        /// Destorys all windows created by the display manager.
        /// </summary>
        ~DisplayManager();

        /// <summary>
        /// Gets a given window based on the input type
        /// </summary>
        /// <param name="type"></param>
        /// <returns></returns>
        DisplayWindow getWindow(DisplayTypes type) { return *m_windows[type]; }

        /// <summary>
        /// Updates a given window based on the input type
        /// </summary>
        /// <param name="type"></param>
        void windowTick(DisplayTypes type);

        /// <summary>
        /// Sets the current glfw context to the given window
        /// </summary>
        /// <param name="type"></param>
        void setCurrentContext(DisplayTypes type) { return glfwMakeContextCurrent(m_windows[type]->handle); }

        /// <summary>
        /// Checks to see if all windows should close
        /// </summary>
        /// <returns></returns>
        bool windowsShouldClose();

    private:
        void initGlfw();
        void initGlad();
        void createDefaultWindow();

    private:
        std::unordered_map<DisplayTypes, std::shared_ptr<DisplayWindow>> m_windows;
    };
}
