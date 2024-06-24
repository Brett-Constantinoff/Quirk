#pragma once
#include "BasePanel.hpp"

namespace Quirk::Editor::Components
{
    class ViewportPanel : public BasePanel
    {
    public:
        ViewportPanel() : BasePanel("Viewport") {}
        ~ViewportPanel() override = default;

        void render() override;
    };
}

