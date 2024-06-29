#include "../../core/eventSystem/EventBus.hpp"
#include "../../core/utils/Defines.hpp"
#include "../../core/utils/ApplicationSettings.hpp"
#include "../../scene/components/MaterialComponent.hpp"
#include "../../scene/components/TransformComponent.hpp"

#include "../utils/Context.hpp"
#include "../utils/Utils.hpp"
#include "MeshFactory.hpp"

#include "Renderer.hpp"

using namespace Quirk::Engine::Core::EventSystem;

using AppSettings = Quirk::Engine::Core::Utils::ApplicationSettings;
using RenderApi = Quirk::Engine::Core::Utils::RenderApi;

namespace Quirk::Engine::Renderer::Rendering
{
	void Renderer::init()
	{
		loadContext();
		chooseAndInitRhi();
		createFramebuffer();

		EventBus::subscribe<WindowResizeEvent>(&Renderer::updateViewport);

		chooseAndInitRhi();
		ShaderManager::init();
		MeshFactory::init();
	}

	void Renderer::shutdown()
	{
		deleteFramebuffer();
		m_rhi->shutdown();
		MeshFactory::shutdown();
		ShaderManager::shutdown();
	}

	void Renderer::tick(double tickSpeed, const DisplayWindow& display, 
		const std::weak_ptr<Scene::Scene> scene)
	{
		onBeforeRenderPass(tickSpeed, display);
		onRenderPass(scene);
	}

	void Renderer::resizeFramebuffer(int width, int height)
	{
		glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::adjustViewport(int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void Renderer::loadContext()
	{
		// load intial settings into our context
		const auto& settings{ AppSettings::getSettings() };

		Utils::Context::renderApi = settings.renderApi;
		Utils::Context::clearColor = settings.clearColor;
		Utils::Context::clearColorBuffer = settings.clearColorBuffer;
		Utils::Context::clearDepthBuffer = settings.clearDepthBuffer;
		Utils::Context::clearStencilBuffer = settings.clearStencilBuffer;
	}

	void Renderer::chooseAndInitRhi()
	{
		switch (Utils::Context::renderApi)
		{
		case RenderApi::OpenGL:
			m_rhi = &m_opengl;
			break;
		default:
			quirkExit("Unsupported render API");
		}
		m_rhi->init();
	}

	void Renderer::updateViewport(const WindowResizeEvent& event)
	{
		const glm::vec2 dimensions{ event.getDim() };
		m_rhi->setViewport(static_cast<uint32_t>(dimensions.x), static_cast<uint32_t>(dimensions.y));
		event.setHandled();
	}

	void Renderer::onBeforeRenderPass(double tickSpeed, const DisplayWindow& display)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
		const auto& clearColor{ Utils::Context::clearColor };
		m_rhi->clearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		m_rhi->clearBuffers(Utils::Context::clearColorBuffer, Utils::Context::clearDepthBuffer, Utils::Context::clearStencilBuffer);
	}

	void Renderer::onRenderPass(const std::weak_ptr<Scene::Scene> scene)
	{
		if (auto scenePtr{ scene.lock() })
		{
			const auto& registry{ scenePtr->getEntities() };
			for (const auto& entity : registry)
			{
				if (entity->isDrawable())
				{
					auto& meshComponent{ entity->getComponent<MeshComponent>() };
					auto& materialComponent{ entity->getComponent<Components::MaterialComponent>() };
					auto& transformComponent{entity->getComponent<Components::TransformComponent>() };

					if (!meshComponent.isSubmitted)
					{
						meshComponent.isSubmitted = true;
						m_rhi->submitDrawData(entity->getId(), meshComponent.vertices, meshComponent.indices, 3, 3);
					}

					auto& material{ ShaderManager::getMaterial(materialComponent.materialId) };

					material->use();
					material->setMat4(transformUniformName, transformComponent.transform);
					material->setVec3(diffuseUniformName, materialComponent.diffuse);
					m_rhi->drawElements(entity->getId(), QuirkPrimitives::Triangles, meshComponent.indexCount);
					material->disuse();
				}
			}
		}
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::createFramebuffer()
	{
		glGenFramebuffers(1, &m_fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

		glGenTextures(1, &m_textureColorbuffer);
		glBindTexture(GL_TEXTURE_2D, m_textureColorbuffer);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textureColorbuffer, 0);

		glGenRenderbuffers(1, &m_rbo);
		glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rbo);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			spdlog::error("ERROR::FRAMEBUFFER:: Framebuffer is not complete!");
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void Renderer::deleteFramebuffer()
	{
		glDeleteFramebuffers(1, &m_fbo);
		glDeleteTextures(1, &m_textureColorbuffer);
		glDeleteRenderbuffers(1, &m_rbo);
	}
}
