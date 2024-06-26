#pragma once
#include "../Component.hpp"

namespace Quirk::Editor::Components
{
    class SceneHierarchyPanel : public Component
    {
    public:
        SceneHierarchyPanel(const std::string& title) { m_title = title; }
        ~SceneHierarchyPanel() override = default;

        void render() override;
    };
}
