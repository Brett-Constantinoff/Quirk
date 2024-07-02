#pragma once
#include "../Component.hpp"
#include <string>

namespace Quirk::Editor::Components
{
    class ViewportPanel : public Component
    {
    public:
        ViewportPanel(const char* title): Component(title){}
        ~ViewportPanel() override = default;

        void render() override;
    };
}
