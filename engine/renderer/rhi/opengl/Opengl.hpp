#pragma once

#include <vector>

#include "../Rhi.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	// TODO - More will be added such as texture buffers etc
	// This will be very expensive to resize as more and more resources are added
	// a solution would be to allocate a large chunk of memory and then use that memory to store the resources
	struct Resources
	{
		std::vector<VertexArray*> vertexArrays{};
		std::vector<VertexBuffer*> vertexBuffers{};
		std::vector<ElementBuffer*> indexBuffers{};
	};

	class Opengl : public Rhi
	{
	public:
		Opengl() = default;
		~Opengl() override;

		void init() override;

		void clearColor(float r, float g, float b, float a) override;
		void clearBuffers(bool color, bool detph, bool stencil) override;
		void submitDrawData(const std::vector<float>& vertexData, const std::vector<qUint32>& indexData, qUint32 vertexDataSize) override;
		void drawElements(Utils::QuirkPrimitives primitiveType, qUint32 indexCount) override;

	private:
		VertexArray* createVertexArray();
		VertexBuffer* createVertexBuffer();
		ElementBuffer* createElementBuffer();

	private:
		Resources m_resources{};
	};
}