#pragma once
#include "../Component.hpp"
#include <string>


namespace Quirk::Editor::Components
{
    class MetricsPanel : public Component
    {
    public:
        MetricsPanel(const std::string& title) { m_title = title; }
        ~MetricsPanel() override = default;

        void render() override;
    };
}
