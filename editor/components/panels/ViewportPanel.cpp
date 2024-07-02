#include "ViewportPanel.hpp"
#include "./renderer/rendering/Renderer.hpp"
#include <core/eventSystem/EventBus.hpp>
#include <core/eventSystem/eventHandlers/EventHandler.hpp>
#include <core/eventSystem/events/ViewportResizeEvent.hpp>

void Quirk::Editor::Components::ViewportPanel::render()
{
    ImGui::Begin(m_title, nullptr, ImGuiWindowFlags_MenuBar);
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

            ViewportResizeEvent event(glm::vec2(panelSize.x, panelSize.y));
            EventBus::publish(event);
        }
        
        // Render the texture to the ImGui window
        auto textureID = Quirk::Engine::Renderer::Rendering::Renderer::getFramebufferTexture();
        ImGui::Image(reinterpret_cast<ImTextureID>(static_cast<uintptr_t>(textureID)), panelSize, ImVec2(0, 1), ImVec2(1, 0));
    }
    ImGui::End();
}
