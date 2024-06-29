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

		EventBus::subscribe<WindowResizeEvent>(&Renderer::updateViewport);

		ShaderManager::init();
		MeshFactory::init();
		m_rhi->createFramebuffer();
	}

	void Renderer::shutdown()
	{
		m_rhi->deleteFramebuffer();
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
		setProjectionMatrix(dimensions.x, dimensions.y);
		event.setHandled();
	}

	void Renderer::setProjectionMatrix(float width, float height)
	{
		float aspectRatio = width / height;
		m_projectionMatrix = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

		// Update the projection matrix in the shader
		ShaderManager::updateProjectionMatrix(m_projectionMatrix);
	}

	void Renderer::onBeforeRenderPass(double tickSpeed, const DisplayWindow& display)
	{
		m_rhi->bindFramebuffer();
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

	void Renderer::resizeFramebuffer(uint32_t width, uint32_t height)
	{
		m_rhi->resizeFramebuffer(width, height);
		setProjectionMatrix(width, height);
	}

	void Renderer::adjustViewport(uint32_t width, uint32_t height)
	{
		m_rhi->setViewport(width, height);
	}

	void Renderer::setRenderModeWireframe() noexcept
	{
		m_rhi->setPolygonModeWireframe();
	}

	void Renderer::setRenderModeSolid() noexcept
	{
		m_rhi->setPolygonModeSolid();
	}

	void Renderer::toggleGizmos() noexcept
	{
		//TODO: implement gizmos
	}
}
