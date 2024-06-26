#pragma once

#include <vector>
#include <memory>
#include <uuid.h>

#include "Utils.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"

#include "../Layout.hpp"
#include "../Rhi.hpp"

using namespace Quirk::Engine::Renderer::Utils;

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	// TODO - More will be added such as texture buffers etc
	// This will be very expensive to resize as more and more resources are added
	// a solution would be to allocate a large chunk of memory and then use that memory to store the resources
	struct Resources
	{
		std::vector<VertexArray> vertexArrays{};
		std::vector<VertexBuffer> vertexBuffers{};
		std::vector<ElementBuffer> indexBuffers{};
	};

	class Opengl : public Rhi
	{
	public:
		void init() override;
		void shutdown() override;

		// utils
		void setViewport(uint32_t width, uint32_t height) override;
		void clearColor(float r, float g, float b, float a) override;
		void clearBuffers(bool color, bool detph, bool stencil) override;

		// buffers
		void submitDrawData(const std::wstring& drawableId, Layout& layout) override;

		// draw
		void drawArrays(const std::wstring& drawableId, QuirkPrimitives primitiveType, uint32_t vertexCount) override;
		void drawElements(const std::wstring& drawableId, QuirkPrimitives primitiveType, uint32_t indexCount) override;

	private:
		VertexArray createVertexArray();
		VertexBuffer createVertexBuffer();
		ElementBuffer createElementBuffer();

	private:
		Resources m_resources{};
		std::unordered_map<std::wstring, VertexArray> m_drawableIdToVao{};
	};
}