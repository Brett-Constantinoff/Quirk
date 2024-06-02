#pragma once
#include <stdint.h>

#include "../utils/Settings.hpp"
#include "../../core/Defines.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Engine::Renderer::Rhi
{
	class Rhi
	{
	public:
		virtual ~Rhi() = default;

		virtual void init() = 0;
		virtual void clearColor(float r, float g, float b, float a) = 0;
		virtual void clearBuffers(bool color, bool detph, bool stencil) = 0;

		virtual void submitDrawData(const std::vector<float>& vertexData, const std::vector<qUint32>& indexData, qUint32 vertexDataSize) = 0;
		virtual void drawElements(Utils::QuirkPrimitives primitiveType, qUint32 indexCount) = 0;
	};
}