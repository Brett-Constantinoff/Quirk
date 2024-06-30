#pragma once

#include <vector>
#include <memory>
#include <uuid.h>

#include "Utils.hpp"
#include "VertexBuffer.hpp"
#include "VertexArray.hpp"
#include "ElementBuffer.hpp"

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
		void setViewport(uint32_t width, uint32_t height) override;
		void clearColor(float r, float g, float b, float a) override;
		void clearBuffers(bool color, bool detph, bool stencil) override;
		void submitDrawData(const std::wstring& drawableId, const std::vector<glm::vec3>& vertexData, uint32_t vertexDataSize, uint32_t stride) override;
		void submitDrawData(const std::wstring& drawableId, const std::vector<glm::vec3>& vertexData, const std::vector<uint32_t>& indexData, uint32_t vertexDataSize, uint32_t stride) override;
		void drawArrays(const std::wstring& drawableId, QuirkPrimitives primitiveType, uint32_t vertexCount) override;
		void drawElements(const std::wstring& drawableId, QuirkPrimitives primitiveType, uint32_t indexCount) override;
		void createFramebuffer() override;
		void deleteFramebuffer() override;
		void resizeFramebuffer(uint32_t width, uint32_t height) override;
		void bindFramebuffer() override;
		void unbindFramebuffer() override;
		void setPolygonModeWireframe() override;
		void setPolygonModeSolid() override;

		uint32_t getFramebufferTexture() const override { return m_textureColorbuffer; }

	private:
		VertexArray createVertexArray();
		VertexBuffer createVertexBuffer();
		ElementBuffer createElementBuffer();

	private:
		Resources m_resources{};
		std::unordered_map<std::wstring, VertexArray> m_drawableIdToVao{};

		uint32_t m_fbo = 0;
		uint32_t m_textureColorbuffer = 0;
		uint32_t m_rbo = 0;
	};
}