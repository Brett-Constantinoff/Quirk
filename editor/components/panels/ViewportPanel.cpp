#include "ViewportPanel.hpp"
#include "./renderer/rendering/Renderer.hpp"

void Quirk::Editor::Components::ViewportPanel::render()
{
    //TODO: Add resize event to update viewport size and aspect ratio for rendering
    ImGui::Begin("Viewport");
    {
        
        ImVec2 wsize = ImGui::GetContentRegionAvail();

        // Resize framebuffer if necessary
        static ImVec2 lastSize = ImVec2(0, 0);
        if (lastSize.x != wsize.x || lastSize.y != wsize.y) {
            lastSize = wsize;
            Quirk::Engine::Renderer::Rendering::Renderer::resizeFramebuffer(static_cast<int>(wsize.x), static_cast<int>(wsize.y));
            Quirk::Engine::Renderer::Rendering::Renderer::adjustViewport(static_cast<int>(wsize.x), static_cast<int>(wsize.y));
        }
        
        // Render the texture to the ImGui window
        auto textureID = Quirk::Engine::Renderer::Rendering::Renderer::getFramebufferTexture();
        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(textureID)), wsize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();
}
