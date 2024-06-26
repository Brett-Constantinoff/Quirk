#pragma once
#include <string>
#include <renderer/gui/ImguiImpl.hpp>

namespace Quirk::Editor::Components
{
	class Component
	{
	public:
		Component() {}
		virtual ~Component() {}
		virtual void render() = 0;
		

	protected:
		std::string m_title;
		bool m_isOpen{ true };

		const std::string& GetTitle() const { return m_title; }
	};
}