#pragma once

#include <glm/glm.hpp>
#include <string>

#include "Settings.hpp"
#include "Defines.hpp"

namespace Quirk::Engine::Core
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
		ApplicationSettings(const ApplicationSettings&) = delete;
		ApplicationSettings(ApplicationSettings&&) = delete;
		ApplicationSettings& operator=(const ApplicationSettings&) = delete;
		ApplicationSettings& operator=(ApplicationSettings&&) = delete;

		static ApplicationSettings& getInstance()
		{
			static ApplicationSettings instance;
			return instance;
		}

		// this allows us to just pass the settings object around
		SettingsObject& getSettings() { return m_settings; }

		void loadDefaults()
		{
			m_settings.isLoaded = true;

			// rendering settings
			m_settings.renderApi = RenderApi::OpenGL;
			m_settings.clearColor = glm::vec4(0.53f, 0.81f, 0.92f, 1.0f);
			m_settings.clearColorBuffer = true;
			m_settings.clearDepthBuffer = false;
			m_settings.clearStencilBuffer = false;
			
			// opengl settings
			m_settings.majorVersion = 4;
			m_settings.minorVersion = 6;

			// display settings
			m_settings.windowWidth = 1200;
			m_settings.windowHeight = 1000;
			m_settings.windowTitle = "Quirk Engine";
		}

	private:
		ApplicationSettings() = default;
		~ApplicationSettings() = default;

		SettingsObject m_settings{};
	};
}
