#pragma once

#include <memory>
#include <glm/glm.hpp>

#include "../../core/eventSystem/EventBus.hpp"
#include "../../core/eventSystem/events/WindowResizeEvent.hpp"
#include "../../display/DisplayWindow.hpp"
#include "../rhi/opengl/Opengl.hpp"
#include "../rhi/Rhi.hpp"
#include "../../scene/Scene.hpp"

#include "ShaderManger.hpp"
#include "Camera.hpp"

using namespace Quirk::Engine::Display;
using namespace Quirk::Engine::Scene;
using namespace Quirk::Engine::Renderer::Rhi;
using namespace Quirk::Engine::Renderer::Rhi::Opengl;
using namespace Quirk::Engine::Core::EventSystem::Events;
using namespace Quirk::Engine::Scene::Components;

namespace Quirk::Engine::Renderer::Rendering
{
    class Renderer
    {
    public:
        static void init();
        static void initSceneData(const std::weak_ptr<Scene::Scene> scene);
        static void shutdown();
        static void tick(double tickSpeed, const DisplayWindow& display,
                         const std::weak_ptr<Scene::Scene> scene);
        static uint32_t getFramebufferTexture() { return m_textureColorbuffer; }

    private:
        static void loadContext();
        static void chooseAndInitRhi();
        static void updateViewport(const WindowResizeEvent& event);

        static void onBeforeRenderPass(double tickSpeed, const DisplayWindow& display);
        static void onRenderPass(const std::weak_ptr<Scene::Scene> scene);

        static void createFramebuffer();
        static void deleteFramebuffer();

    private:
        inline static Rhi::Rhi* m_rhi{nullptr};
        inline static Rhi::Opengl::Opengl m_opengl{};
        inline static uint32_t m_fbo = 0;
        inline static uint32_t m_textureColorbuffer = 0;
        inline static uint32_t m_rbo = 0;
    };
}
