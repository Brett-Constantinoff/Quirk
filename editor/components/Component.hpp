#pragma once
#include <string>
#include <renderer/gui/ImguiImpl.hpp>

namespace Quirk::Editor::Components
{
	class Component
	{
	public:
		Component(const char* title){m_title = title;}
		Component() = default;
		virtual ~Component() {}
		virtual void render() = 0;
		

	protected:
		const char* m_title;
		bool m_isOpen{ true };

		const char* GetTitle() const { return m_title; }
	};
}