#pragma once

#include <stdint.h>
#include <vector>

#include "../utils/Settings.hpp"
#include "../../core/utils/Defines.hpp"

using namespace Quirk::Engine::Core::Utils;
using namespace Quirk::Engine::Renderer::Utils;

namespace Quirk::Engine::Renderer::Rhi
{
	class Rhi
	{
	public:
		virtual ~Rhi() {};

		virtual void init() = 0;
		virtual void setViewport(qUint32 width, qUint32 height) = 0;
		virtual void clearColor(float r, float g, float b, float a) = 0;
		virtual void clearBuffers(bool color, bool detph, bool stencil) = 0;

		virtual void submitDrawData(const std::vector<float>& vertexData, qUint32 vertexDataSize, qUint32 stride) = 0;
		virtual void submitDrawData(const std::vector<float>& vertexData, const std::vector<qUint32>& indexData, qUint32 vertexDataSize, qUint32 stride) = 0;
		virtual void drawArrays(QuirkPrimitives primitiveType, qUint32 vertexCount) = 0;
		virtual void drawElements(QuirkPrimitives primitiveType, qUint32 indexCount) = 0;
	};
}