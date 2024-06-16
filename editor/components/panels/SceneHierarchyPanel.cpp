#include "SceneHierarchyPanel.hpp"

namespace Quirk::Editor::Components
{
    void SceneHierarchyPanel::render()
    {
        // Set up the docking properties
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize;
        
        if (ImGui::Begin(m_title.c_str(), nullptr, window_flags))
        {
            ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0, 0, 0, 1));
            //ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.2f, 0.3f, 0.8f, 1.0f));
            // Create a child window for the panel content
            ImGui::BeginChild("Panel Content", ImVec2(0, 0), true, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
            // Here you can add any content for your panel
            ImGui::Text("Scene Hierarchy Panel Content");

            ImGui::EndChild();
            ImGui::PopStyleColor();
            ImGui::End();
        }
    }
}
