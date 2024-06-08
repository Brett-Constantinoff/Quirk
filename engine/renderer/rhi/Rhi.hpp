#pragma once

#include <stdint.h>
#include <vector>

#include "../utils/Settings.hpp"

using namespace Quirk::Engine::Renderer::Utils;

namespace Quirk::Engine::Renderer::Rhi
{
	class Rhi
	{
	public:
		virtual ~Rhi() {};

		virtual void init() = 0;
		virtual void setViewport(uint32_t width, uint32_t height) = 0;
		virtual void clearColor(float r, float g, float b, float a) = 0;
		virtual void clearBuffers(bool color, bool detph, bool stencil) = 0;

		virtual void submitDrawData(const std::vector<float>& vertexData, uint32_t vertexDataSize, uint32_t stride) = 0;
		virtual void submitDrawData(const std::vector<float>& vertexData, const std::vector<uint32_t>& indexData, uint32_t vertexDataSize, uint32_t stride) = 0;
		virtual void drawArrays(QuirkPrimitives primitiveType, uint32_t vertexCount) = 0;
		virtual void drawElements(QuirkPrimitives primitiveType, uint32_t indexCount) = 0;
	};
}