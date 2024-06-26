#pragma once
#include "../Component.hpp"
#include <string>

namespace Quirk::Editor::Components
{
    class ViewportPanel : public Component
    {
    public:
        ViewportPanel(const std::string& title) { m_title = "Viewport"; }
        ~ViewportPanel() override = default;

        void render() override;
    };
}
