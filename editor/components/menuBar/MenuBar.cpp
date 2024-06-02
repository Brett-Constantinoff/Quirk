#include "MenuBar.hpp"

namespace Quirk::Editor::Components::MenuBar
{
	MenuBar::~MenuBar()
	{
	}

	void MenuBar::render()
	{
		if (ImGui::BeginMainMenuBar())
		{
			renderFileMenu();
			renderSettingsMenu();
			ImGui::EndMainMenuBar();
		}
	}

	void MenuBar::renderFileMenu()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New"))
			{
			}
			if (ImGui::MenuItem("Open"))
			{
			}
			if (ImGui::MenuItem("Save"))
			{
			}
			ImGui::EndMenu();
		}

	}

	void MenuBar::renderSettingsMenu()
	{
		if (ImGui::BeginMenu("Settings"))
		{
			if (ImGui::MenuItem("General"))
			{
			}

			if (ImGui::MenuItem("Editor"))
			{
			}
			ImGui::EndMenu();
		}
	}
}