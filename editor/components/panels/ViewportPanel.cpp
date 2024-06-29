#include "ViewportPanel.hpp"
#include "./renderer/rendering/Renderer.hpp"

void Quirk::Editor::Components::ViewportPanel::render()
{
    //TODO: we need to render the viewport here
    // We can accomplish this by rendering our stuff in OpenGL to a texture
    // to a framebuffer and then just display that image here in the viewport.

    // For now, we will just render a simple ImGui window with the title "Viewport" and the image of our logo
    ImGui::Begin("Viewport");
    {
        ImVec2 wsize = ImGui::GetContentRegionAvail();
        ImGui::Image((ImTextureID)Quirk::Engine::Renderer::Rendering::Renderer::getFramebufferTexture(), wsize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();
}
