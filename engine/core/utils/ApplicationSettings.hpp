#pragma once

#include <string>

#include <glm/glm.hpp>

#include "Defines.hpp"

namespace Quirk::Engine::Core::Utils
{
	enum class RenderApi
	{
		OpenGL,
		//Vulkan, // LOL yeah right
	};

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
		uint32_t majorVersion{};
		uint32_t minorVersion{};

		// display settings
		uint32_t windowWidth{};
		uint32_t windowHeight{};
		std::string_view windowTitle{};
	};

	class ApplicationSettings
	{
	public:
		// this allows us to just pass the settings object around
		static SettingsObject& getSettings();
		static void loadDefaults();
		static void setOpenglVersion(uint32_t major, uint32_t minor);

	private:
		inline static SettingsObject m_settings{};
	};
}
