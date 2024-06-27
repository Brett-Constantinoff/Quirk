#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <glad/glad.h>

#include "../../../core/utils/Utils.hpp"
#include "../../../core/utils/ApplicationSettings.hpp"

#include "Opengl.hpp"

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

		glFrontFace(GL_CCW);

		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(debugCallback, nullptr);

		const GLubyte* renderer{ glGetString(GL_RENDERER) };
		const GLubyte* vendor{ glGetString(GL_VENDOR) };
		const GLubyte* version{ glGetString(GL_VERSION) };
		const GLubyte* glslVersion{ glGetString(GL_SHADING_LANGUAGE_VERSION) };

		int32_t majorVersion{ 0 };
		int32_t minorVersion{ 0 };

		glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);

		glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

		spdlog::info("GPU: {}", reinterpret_cast<const char*>(renderer));
		spdlog::info("Vendor: {}", reinterpret_cast<const char*>(vendor));
		spdlog::info("Version: {}", reinterpret_cast<const char*>(version));
		spdlog::info("GLSL Version: {}", reinterpret_cast<const char*>(glslVersion));
		spdlog::info("OpenGL Version: {}.{}", majorVersion, minorVersion);

		AppSettings::setOpenglVersion(majorVersion, minorVersion);
	}

	void Opengl::shutdown()
	{
		for (std::size_t i{ 0 }; i < m_resources.vertexArrays.size(); ++i)
			glDeleteVertexArrays(1, &(m_resources.vertexArrays[i].getId()));
		for (std::size_t i{ 0 }; i < m_resources.vertexBuffers.size(); ++i)
			glDeleteBuffers(1, &(m_resources.vertexBuffers[i].getId()));
		for (std::size_t i{ 0 }; i < m_resources.indexBuffers.size(); ++i)
			glDeleteBuffers(1, &(m_resources.indexBuffers[i].getId()));

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

	void Opengl::setViewport(uint32_t width, uint32_t height)
	{
		glViewport(0, 0, width, height);
	}

	void Opengl::submitDrawData(const std::wstring& drawableId, const std::vector<glm::vec3>& vertexData, uint32_t vertexDataSize, uint32_t stride)
	{
		auto vao{ createVertexArray() };
		const auto vbo{ createVertexBuffer() };

		vao.bind();

		vbo.bind();
		vbo.setData(vertexData.data(), static_cast<uint32_t>(vertexData.size()) * sizeof(glm::vec3));

		vao.setData(vertexDataSize, stride);

		vbo.unbind();
		vao.unbind();

		m_drawableIdToVao[drawableId] = vao;
	}

	void Opengl::submitDrawData(const std::wstring& drawableId, const std::vector<glm::vec3>& vertexData, const std::vector<uint32_t>& indexData, uint32_t vertexDataSize, uint32_t stride)
	{
		auto vao{ createVertexArray() };
		const auto vbo{ createVertexBuffer() };
		const auto ebo{ createElementBuffer() };

		vao.bind();

		vbo.bind();
		vbo.setData(vertexData.data(), static_cast<uint32_t>(vertexData.size()) * sizeof(glm::vec3));

		ebo.bind();
		ebo.setData(indexData.data(), static_cast<uint32_t>(indexData.size()) * sizeof(uint32_t));

		vao.setData(vertexDataSize, stride);

		vbo.unbind();
		vao.unbind();

		m_drawableIdToVao[drawableId] = vao;
	}

	void Opengl::drawElements(const std::wstring& drawableId, QuirkPrimitives primitiveType, uint32_t indexCount)
	{
		const auto& vao{ m_drawableIdToVao[drawableId] };

		vao.bind();
		glDrawElements(mapPrimitiveToGl(primitiveType), indexCount, GL_UNSIGNED_INT, 0);
		vao.unbind();
	}

	void Opengl::drawArrays(const std::wstring& drawableId, QuirkPrimitives primitiveType, uint32_t vertexCount)
	{
		const auto& vao{ m_drawableIdToVao[drawableId] };

		vao.bind();
		glDrawArrays(mapPrimitiveToGl(primitiveType), 0, vertexCount);
		vao.unbind();
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