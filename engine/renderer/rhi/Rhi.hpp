#pragma once

#include <stdint.h>
#include <vector>
#include <glm/glm.hpp>
#include <uuid.h>

#include "../utils/Settings.hpp"
#include "Layout.hpp"

using namespace Quirk::Engine::Renderer::Utils;

namespace Quirk::Engine::Renderer::Rhi
{
	class Rhi
	{
	public:
		virtual ~Rhi() {};

		virtual void init() = 0;
		virtual void shutdown() = 0;

		virtual void setViewport(uint32_t width, uint32_t height) = 0;
		virtual void clearColor(float r, float g, float b, float a) = 0;
		virtual void clearBuffers(bool color, bool detph, bool stencil) = 0;

		virtual void submitDrawData(const std::wstring& drawableId, Layout& layout) = 0;

		virtual void drawArrays(const std::wstring& drawableId, QuirkPrimitives primitiveType, uint32_t vertexCount) = 0;
		virtual void drawElements(const std::wstring& drawableId, QuirkPrimitives primitiveType, uint32_t indexCount) = 0;
		virtual void createFramebuffer() = 0;
		virtual void deleteFramebuffer() = 0;
		virtual void resizeFramebuffer(uint32_t width, uint32_t height) = 0;
		virtual void bindFramebuffer() = 0;
		virtual void unbindFramebuffer() = 0;

		virtual void setPolygonModeWireframe() = 0;
		virtual void setPolygonModeSolid() = 0;

		virtual uint32_t getFramebufferTexture() const = 0;
	};
}