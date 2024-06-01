#include "Editor.hpp"

namespace Quirk::Editor
{
	Editor::Editor() : 
		 m_displayManager{},
		 m_components{}
	{
	}

	Editor::~Editor()
	{
	}

	void Editor::tick()
	{
		setup();

		const auto& display{m_displayManager.getWindow(DisplayTypes::Default)};
		while (!m_displayManager.windowsShouldClose())
		{
			renderEditor();
			m_displayManager.windowTick(DisplayTypes::Default);
		}
	}

	void Editor::setup()
	{
		Imgui_Impl::getInstance().setup(m_displayManager.getWindow(DisplayTypes::Default).handle);
		m_components.push_back(std::make_unique<MenuBar::MenuBar>());
	}

	void Editor::renderEditor()
	{
		Imgui_Impl::getInstance().updateFrame();

		for (auto& component : m_components)
			component->render();

		Imgui_Impl::getInstance().renderFrame();
	}
}