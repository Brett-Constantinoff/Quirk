#pragma once
#include "BasePanel.hpp"

namespace Quirk::Editor::Components
{
    class MetricsPanel : public BasePanel
    {
    public:
        MetricsPanel() : BasePanel("Metrics") {}
        ~MetricsPanel() override = default;

        void render() override;
    };
}
