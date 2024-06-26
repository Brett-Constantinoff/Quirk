#include "ViewportPanel.hpp"

void Quirk::Editor::Components::ViewportPanel::render()
{
    //TODO: we need to render the viewport here
    // We can accomplish this by rendering our stuff in OpenGL to a texture
    // to a framebuffer and then just display that image here in the viewport.

    // For now, we will just render a simple ImGui window with the title "Viewport" and the image of our logo
    ImGui::Begin("Viewport");
    ImGui::End();
}
