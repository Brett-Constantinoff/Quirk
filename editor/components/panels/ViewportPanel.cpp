#include "ViewportPanel.hpp"
#include "./renderer/rendering/Renderer.hpp"

void Quirk::Editor::Components::ViewportPanel::render()
{
    //TODO: Add resize event to update viewport size and aspect ratio for rendering
    ImGui::Begin("Viewport");
    {
        ImVec2 wsize = ImGui::GetContentRegionAvail();
        ImGui::Image(reinterpret_cast<ImTextureID>(Quirk::Engine::Renderer::Rendering::Renderer::getFramebufferTexture()), wsize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();
}
