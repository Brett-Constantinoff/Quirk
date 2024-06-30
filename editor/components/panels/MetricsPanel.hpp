#pragma once
#include "../Component.hpp"
#include <string>


namespace Quirk::Editor::Components
{
    class MetricsPanel : public Component
    {
    public:
        MetricsPanel(const char* title) { m_title = title; }
        ~MetricsPanel() override = default;

        void render() override;
    };
}
