#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Settings.hpp"
#include "Defines.hpp"

namespace Quirk::Engine::Core::Utils
{
	// as this grows it will become very expensive to copy
	// so ALWAYS pass by reference
	struct SettingsObject
	{
		bool isLoaded{ false };

		// rendering settings
		RenderApi renderApi{};
		glm::vec4 clearColor{};
		bool clearColorBuffer{};
		bool clearDepthBuffer{};
		bool clearStencilBuffer{};
		bool is3d{};

		// opengl settings
		qUint32 majorVersion{};
		qUint32 minorVersion{};

		// display settings
		qUint32 windowWidth{};
		qUint32 windowHeight{};
		std::string_view windowTitle{};
	};

	class ApplicationSettings
	{
	public:
		// this allows us to just pass the settings object around
		static SettingsObject& getSettings() { return m_settings; }

		static void loadDefaults()
		{
			m_settings.isLoaded = true;

			// rendering settings
			m_settings.renderApi = RenderApi::OpenGL;
			m_settings.clearColor = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f);
			m_settings.clearColorBuffer = true;
			m_settings.clearDepthBuffer = true;
			m_settings.clearStencilBuffer = false;
			m_settings.is3d = true;

			// display settings
			m_settings.windowWidth = 1200;
			m_settings.windowHeight = 1000;
			m_settings.windowTitle = "Quirk Engine";
		}

		static void setOpenglVersion(qUint32 major, qUint32 minor)
		{
			m_settings.majorVersion = major;
			m_settings.minorVersion = minor;
		}

	private:
		inline static SettingsObject m_settings{};
	};
}
