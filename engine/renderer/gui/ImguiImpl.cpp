#include "ImguiImpl.hpp"

#include "GLFW/glfw3.h"

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
        ImGui::ShowDemoWindow();
        ImGui::DockSpaceOverViewport();
        
    }

    void ImguiImpl::renderFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    
}
