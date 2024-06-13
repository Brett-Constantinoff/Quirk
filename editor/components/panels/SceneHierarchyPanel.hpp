#pragma once
#include "BasePanel.hpp"

namespace Quirk::Editor::Components
{
    class SceneHierarchyPanel : public BasePanel
    {
    public:
        SceneHierarchyPanel() : BasePanel("Scene Hierarchy") {}
        ~SceneHierarchyPanel() override = default;

        void render() override;
    };
}
