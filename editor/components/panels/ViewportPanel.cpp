#include "ViewportPanel.hpp"
#include "./renderer/rendering/Renderer.hpp"

void Quirk::Editor::Components::ViewportPanel::render()
{
    //TODO: Add resize event to update viewport size and aspect ratio for rendering
    ImGui::Begin("Viewport", nullptr, ImGuiWindowFlags_MenuBar);
    {
        // Options bar
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("Options")) {
                if (ImGui::MenuItem("Wireframe")) {
                    Quirk::Engine::Renderer::Rendering::Renderer::setRenderModeWireframe();
                }
                if (ImGui::MenuItem("Solid")) {
                    Quirk::Engine::Renderer::Rendering::Renderer::setRenderModeSolid();
                }
                if (ImGui::MenuItem("Toggle Gizmos")) {
                    Quirk::Engine::Renderer::Rendering::Renderer::toggleGizmos();
                }
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }
        
        ImVec2 panelSize = ImGui::GetContentRegionAvail();

        // Resize framebuffer if necessary
        static ImVec2 lastSize = ImVec2(0, 0);
        if (lastSize.x != panelSize.x || lastSize.y != panelSize.y) {
            lastSize = panelSize;
            Quirk::Engine::Renderer::Rendering::Renderer::resizeFramebuffer(static_cast<int>(panelSize.x), static_cast<int>(panelSize.y));
            Quirk::Engine::Renderer::Rendering::Renderer::adjustViewport(static_cast<int>(panelSize.x), static_cast<int>(panelSize.y));
        }
        
        // Render the texture to the ImGui window
        auto textureID = Quirk::Engine::Renderer::Rendering::Renderer::getFramebufferTexture();
        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(textureID)), panelSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();
}
