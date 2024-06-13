#include "SceneHierarchyPanel.hpp"

namespace Quirk::Editor::Components
{
    void SceneHierarchyPanel::render()
    {
        // Set up the docking properties
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        
        if (ImGui::Begin(m_title.c_str(), nullptr, window_flags))
        {
            // Here you can add any content for your panel
            ImGui::Text("Scene Hierarchy Panel Content");

            ImGui::End();
        }
    }
}
