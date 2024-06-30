#pragma once
#include "../Component.hpp"
#include <string>

namespace Quirk::Editor::Components
{
    class ViewportPanel : public Component
    {
    public:
        ViewportPanel(const char* title) { m_title = title; }
        ~ViewportPanel() override = default;

        void render() override;
    };
}
