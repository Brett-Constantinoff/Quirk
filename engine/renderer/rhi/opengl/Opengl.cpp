#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include "Opengl.hpp"

#include "../../../core/utils/Utils.hpp"
#include "../../../core/utils/ApplicationSettings.hpp"

using namespace Quirk::Engine::Renderer::Utils;
using namespace Quirk::Engine::Core::Utils;

using AppSettings = Quirk::Engine::Core::Utils::ApplicationSettings;

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	void Opengl::init()
	{
		const auto& settings{ AppSettings::getSettings() };
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			quirkExit("Failed to initialize Glad");

		if (settings.is3d)
			glEnable(GL_DEPTH_TEST);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(debugCallback, nullptr);

		const GLubyte* renderer{ glGetString(GL_RENDERER) };
		const GLubyte* vendor{ glGetString(GL_VENDOR) };
		const GLubyte* version{ glGetString(GL_VERSION) };
		const GLubyte* glslVersion{ glGetString(GL_SHADING_LANGUAGE_VERSION) };

		qInt32 majorVersion{ 0 };
		qInt32 minorVersion{ 0 };

		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);

		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

		spdlog::info("GPU: {}", reinterpret_cast<const char*>(renderer));
		spdlog::info("Vendor: {}", reinterpret_cast<const char*>(vendor));
		spdlog::info("Version: {}", reinterpret_cast<const char*>(version));
		spdlog::info("GLSL Version: {}", reinterpret_cast<const char*>(glslVersion));
		spdlog::info("OpenGL Version: {}.{}", majorVersion, minorVersion);

		AppSettings::setOpenglVersion(majorVersion, minorVersion);
	}

	void Opengl::shutDown()
	{
		for (auto& vao : m_resources.vertexArrays)
			glDeleteVertexArrays(1, &(vao.getId()));
		for (auto& vbo : m_resources.vertexBuffers)
			glDeleteBuffers(1, &(vbo.getId()));
		for (auto& ebo : m_resources.indexBuffers)
			glDeleteBuffers(1, &(ebo.getId()));

		m_resources.vertexBuffers.clear();
		m_resources.vertexArrays.clear();
		m_resources.indexBuffers.clear();
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

	void Opengl::setViewport(qUint32 width, qUint32 height)
	{
		glViewport(0, 0, width, height);
	}

	void Opengl::submitDrawData(const std::vector<float>& vertexData, qUint32 vertexDataSize, qUint32 stride)
	{
		auto vao{ createVertexArray() };
		const auto vbo{ createVertexBuffer() };

		vao.bind();

		vbo.bind();
		vbo.setData(vertexData.data(), vertexData.size() * sizeof(float));

		vao.setData(vertexDataSize, stride);

		vbo.unbind();
		vao.unbind();
	}

	void Opengl::submitDrawData(const std::vector<float>& vertexData, const std::vector<qUint32>& indexData, qUint32 vertexDataSize, qUint32 stride)
	{
		auto vao{ createVertexArray() };
		const auto vbo{ createVertexBuffer() };
		const auto ebo{ createElementBuffer() };

		vao.bind();

		vbo.bind();
		vbo.setData(vertexData.data(), vertexData.size() * sizeof(float));

		ebo.bind();
		ebo.setData(indexData.data(), vertexData.size() * sizeof(qUint32));

		vao.setData(vertexDataSize, stride);

		vbo.unbind();
		vao.unbind();
	}

	void Opengl::drawElements(QuirkPrimitives primitiveType, qUint32 indexCount)
	{
		// TODO - since theres only one vao this is fine for now
		m_resources.vertexArrays.back().bind();

		glDrawElements(mapPrimitiveToGl(primitiveType), indexCount, GL_UNSIGNED_INT, 0);

		m_resources.vertexArrays.back().unbind();
	}

	void Opengl::drawArrays(QuirkPrimitives primitiveType, qUint32 vertexCount)
	{
		m_resources.vertexArrays.back().bind();

		glDrawArrays(mapPrimitiveToGl(primitiveType), 0, vertexCount);

		m_resources.vertexArrays.back().unbind();
	}

	VertexArray Opengl::createVertexArray()
	{
		auto vao{ VertexArray() };
		m_resources.vertexArrays.emplace_back(vao);

		return vao;
	}

	VertexBuffer Opengl::createVertexBuffer()
	{
		auto vbo{ VertexBuffer() };
		m_resources.vertexBuffers.emplace_back(vbo);

		return vbo;
	}

	ElementBuffer Opengl::createElementBuffer()
	{
		auto ebo{ ElementBuffer() };
		m_resources.indexBuffers.emplace_back(ebo);

		return ebo;
	}
}