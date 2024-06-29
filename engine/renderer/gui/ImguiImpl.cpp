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
        //ImGui::ShowDemoWindow();
        ImGui::DockSpaceOverViewport();

        //--CONSOLE--
        static Editor::Uitls::ExampleAppConsole console;
        console.Draw("Console",nullptr);
        //--END CONSOLE--

        //--LOG--
        static Editor::Uitls::ExampleAppLog log; 

        // For the demo: add a debug button _BEFORE_ the normal log window contents
        // We take advantage of a rarely used feature: multiple calls to Begin()/End() are appending to the _same_ window.
        // Most of the contents of the window will be added by the log.Draw() call.
        ImGui::SetNextWindowSize(ImVec2(500, 400), ImGuiCond_FirstUseEver);
        ImGui::Begin("Example: Log");
        
        //DEMO CODE FOR SHOWING A BUTTON
        // if (ImGui::SmallButton("[Debug] Add 5 entries"))
        // {
        //     static int counter = 0;
        //     const char* categories[3] = { "info", "warn", "error" };
        //     const char* words[] = { "Bumfuzzled", "Cattywampus", "Snickersnee", "Abibliophobia", "Absquatulate", "Nincompoop", "Pauciloquent" };
        //     for (int n = 0; n < 5; n++)
        //     {
        //         const char* category = categories[counter % IM_ARRAYSIZE(categories)];
        //         const char* word = words[counter % IM_ARRAYSIZE(words)];
        //         log.AddLog("[%05d] [%s] Hello, current time is %.1f, here's a word: '%s'\n",
        //             ImGui::GetFrameCount(), category, ImGui::GetTime(), word);
        //         counter++;
        //     }
        // }

        // Display logs from spdlog
        // if (auto imgui_sink = std::dynamic_pointer_cast<Quirk::Engine::Renderer::Utils::ImGuiSink_mt>(spdlog::get("logger")->sinks()[0]))
        // {
        //     auto& log_messages = imgui_sink->GetLogMessages();
        //     for (const auto& msg : log_messages)
        //     {
        //         ImGui::TextUnformatted(msg.c_str());
        //     }
        // }
        // else
        // {
        //     spdlog::error("Failed to cast sink to ImGuiSink_mt");
        //     spdlog::error("GUI Logging will not work!");
        // }
        
        ImGui::End();
        // Actually call in the regular Log helper (which will Begin() into the same window as we just did)
        log.Draw("Example: Log", nullptr);
        //--END LOG--
        
    }

    void ImguiImpl::renderFrame()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    
}
