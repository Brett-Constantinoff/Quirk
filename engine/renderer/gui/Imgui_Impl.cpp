#include "Imgui_Impl.hpp"

namespace Quirk::Engine::Renderer::Gui
{
	Imgui_Impl::~Imgui_Impl()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void Imgui_Impl::setup(GLFWwindow* currentContext)
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		ImGui::StyleColorsClassic();
		ImGuiStyle& style = ImGui::GetStyle();
		style.Alpha = 1.0f;

		ImGui_ImplGlfw_InitForOpenGL(currentContext, true);
		ImGui_ImplOpenGL3_Init("#version 150");
	}

	void Imgui_Impl::updateFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void Imgui_Impl::renderFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}