#include "ImguiImpl.hpp"

#include "../../../editor/utils/Utils.hpp"
#include "GLFW/glfw3.h"
#include "../utils/ImGuiSink.hpp"

namespace Quirk::Engine::Renderer::Gui
{
    void ImguiImpl::init(GLFWwindow* currentContext)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

        ImGuiStyle& style = ImGui::GetStyle();

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Alpha = 1.0f;
        }

        //ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(currentContext, true);
        ImGui_ImplOpenGL3_Init("#version 150");

        // Initialize spdlog with ImGuiSink
        Quirk::Engine::Renderer::Utils::init_logging();
    }

    void ImguiImpl::shutdown()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void ImguiImpl::updateFrame()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
#ifdef DEBUG
        //ImGui::ShowDemoWindow(); //TODO: Remove this before release, leaving it here for easy access to the demo window
#endif
        ImGui::DockSpaceOverViewport();
    }

    void ImguiImpl::renderFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    
}
