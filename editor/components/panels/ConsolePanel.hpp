#pragma once
#include "../Component.hpp"

namespace Quirk::Editor::Components
{
    class ConsolePanel : public Component
    {
    public:
        ConsolePanel(const char* title) { m_title = title; }
        ~ConsolePanel() override = default;

        void render() override;
    };
}
