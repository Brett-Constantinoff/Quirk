#include "MetricsPanel.hpp"

void Quirk::Editor::Components::MetricsPanel::render()
{
    ImGui::Begin(m_title, nullptr, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize);
    ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::Text("Frame Time: %.3f ms", 1000.0f / ImGui::GetIO().Framerate);
    ImGui::End();
}
