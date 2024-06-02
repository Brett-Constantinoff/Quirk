#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Opengl.hpp"

#include "../../../core/Utils.hpp"
#include "../../utils/Utils.hpp"

using namespace Quirk::Engine::Renderer::Utils;

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	Opengl::~Opengl()
	{
		for (auto& vao : m_resources.vertexArrays)
		{
			glDeleteVertexArrays(1, &(vao->getId()));
			delete vao;
		}
		for (auto& vbo : m_resources.vertexBuffers)
		{
			glDeleteBuffers(1, &(vbo->getId()));
			delete vbo;
		}
		for (auto& ebo : m_resources.indexBuffers)
		{
			glDeleteBuffers(1, &(ebo->getId()));
			delete ebo;
		}
		m_resources.vertexBuffers.clear();
		m_resources.vertexBuffers.shrink_to_fit();
		m_resources.vertexArrays.clear();
		m_resources.vertexArrays.shrink_to_fit();
		m_resources.indexBuffers.clear();
		m_resources.indexBuffers.shrink_to_fit();
	}

	void Opengl::init()
	{
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			Core::Utils::Exit("Failed to initialize Glad");
	}

	void Opengl::clearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	void Opengl::clearBuffers(bool color, bool detph, bool stencil)
	{
		GLbitfield mask{ 0 };

		if (color)
			mask |= GL_COLOR_BUFFER_BIT;
		if (detph)
			mask |= GL_DEPTH_BUFFER_BIT;
		if (stencil)
			mask |= GL_STENCIL_BUFFER_BIT;
		
		if (mask != 0)
			glClear(mask);
	}

	void Opengl::submitDrawData(const std::vector<float>& vertexData, const std::vector<qUint32>& indexData, qUint32 vertexDataSize)
	{
		const auto& vao{ createVertexArray() };
		const auto& vbo{ createVertexBuffer() };
		const auto& ebo{ createElementBuffer() };

		vao->bind();

		vbo->bind();
		vbo->setData(vertexData.data(), vertexData.size() * sizeof(float));

		ebo->bind();
		ebo->setData(indexData.data(), vertexData.size() * sizeof(qUint32));

		vao->setData(vertexDataSize, vertexDataSize * sizeof(float));

		vbo->unbind();
		vao->unbind();
	}

	void Opengl::drawElements(Utils::QuirkPrimitives primitiveType, qUint32 indexCount)
	{
		// TODO - since theres only one vao this is fine for now
		m_resources.vertexArrays.back()->bind();

		glDrawElements(Utils::Utils::mapPrimitiveToGl(primitiveType), indexCount, GL_UNSIGNED_INT, 0);

		m_resources.vertexArrays.back()->unbind();
	}

	VertexArray* Opengl::createVertexArray()
	{
		auto* vao{new VertexArray() };
		m_resources.vertexArrays.emplace_back(vao);

		return vao;
	}

	VertexBuffer* Opengl::createVertexBuffer()
	{
		auto* vbo{new VertexBuffer() };
		m_resources.vertexBuffers.emplace_back(vbo);

		return vbo;
	}

	ElementBuffer* Opengl::createElementBuffer()
	{
		auto* ebo{ new ElementBuffer() };
		m_resources.indexBuffers.emplace_back(ebo);

		return ebo;
	}
}