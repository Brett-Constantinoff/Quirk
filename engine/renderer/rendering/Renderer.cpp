#include "../../core/eventSystem/EventBus.hpp"
#include "../../core/utils/Defines.hpp"
#include "../../core/utils/ApplicationSettings.hpp"

#include "../utils/Context.hpp"
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

		// subscribe for any events
		EventBus::subscribe<WindowResizeEvent>(&Renderer::updateViewport);

		// create our materials
		ShaderManager::init();

		// init the mesh factory
		MeshFactory::init();

		// TODO - The scene should be separeted from rendering, this is just a test
		// the scene should be updated by the user so it should be handled by the editor
		setupBasicScene();
	}

	void Renderer::shutdown()
	{
		m_rhi->shutdown();
		MeshFactory::shutdown();
		ShaderManager::shutdown();
	}

	void Renderer::tick(double tickSpeed, const DisplayWindow& display)
	{
		onBeforeRenderPass(tickSpeed, display);
		onRenderPass();
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

	void Renderer::setupBasicScene()
	{
		auto& entity{ m_scene->createEntity("Clown Quad")};

		auto meshComponent{ MeshFactory::createMesh(MeshTypes::Quad, m_rhi) };
		entity->addComponent<MeshComponent>(*meshComponent);
		entity->setDrawable(true);

		MaterialComponent materialComponent{};
		materialComponent.materialId = ShaderManager::getMaterialId(MaterialType::Basic2D);
		entity->addComponent<MaterialComponent>(materialComponent);
	}

	void Renderer::onBeforeRenderPass(double tickSpeed, const DisplayWindow& display)
	{
		const auto& clearColor{ Utils::Context::clearColor };
		m_rhi->clearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		m_rhi->clearBuffers(Utils::Context::clearColorBuffer, Utils::Context::clearDepthBuffer, Utils::Context::clearStencilBuffer);
	}

	void Renderer::onRenderPass()
	{
		const auto& registry{ m_scene->getEntities() };
		for (const auto& entity : registry)
		{
			if (entity->isDrawable())
			{
				auto& meshComponent{ entity->getComponent<MeshComponent>() };
				auto& MaterialComponent{ entity->getComponent<Components::MaterialComponent>() };

				auto& material{ ShaderManager::getMaterial(MaterialComponent.materialId) };

				material->use();
				m_rhi->drawElements(QuirkPrimitives::Triangles, meshComponent.indexCount);
				material->disuse();
			}
		}
	}
}
