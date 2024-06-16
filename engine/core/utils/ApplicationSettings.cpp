#include "ApplicationSettings.hpp"

namespace Quirk::Engine::Core::Utils
{
	SettingsObject& ApplicationSettings::getSettings() 
	{ 
		return m_settings; 
	}

	void ApplicationSettings::loadDefaults()
	{
		m_settings.isLoaded = true;

		// rendering settings
		m_settings.renderApi = RenderApi::OpenGL;
		m_settings.clearColor = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
		m_settings.clearColorBuffer = true;
		m_settings.clearDepthBuffer = true;
		m_settings.clearStencilBuffer = false;
		m_settings.is3d = true;

		// display settings
		m_settings.windowWidth = 1200;
		m_settings.windowHeight = 1000;
		m_settings.windowTitle = "Quirk Engine";
	}

	void ApplicationSettings::setOpenglVersion(uint32_t major, uint32_t minor)
	{
		m_settings.majorVersion = major;
		m_settings.minorVersion = minor;
	}
}