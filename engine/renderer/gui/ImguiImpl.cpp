#include "ImguiImpl.hpp"

namespace Quirk::Engine::Renderer::Gui
{
	ImguiImpl::~ImguiImpl()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImguiImpl::init(GLFWwindow* currentContext)
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

	void ImguiImpl::updateFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImguiImpl::renderFrame()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}
}