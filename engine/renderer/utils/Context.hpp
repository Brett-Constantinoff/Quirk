#pragma once

#include <glm/glm.hpp>

#include "../../core/utils/ApplicationSettings.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Renderer::Utils
{
	struct Context
	{
	public:
		inline static RenderApi renderApi{};
		inline static glm::vec4 clearColor{};
		inline static bool clearColorBuffer{};
		inline static bool clearDepthBuffer{};
		inline static bool clearStencilBuffer{};
	};
}