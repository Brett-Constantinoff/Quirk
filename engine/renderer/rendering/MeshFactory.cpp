#include "../../core/eventSystem/EventBus.hpp"
#include "../../core/eventSystem/events/MeshCreationEvent.hpp"

#include "MeshFactory.hpp"

using namespace Quirk::Engine::Core::EventSystem;

namespace Quirk::Engine::Renderer::Rendering
{
    void MeshFactory::init()
    {
        m_meshCache.reserve(static_cast<size_t>(MeshTypes::Count));
    }

    void MeshFactory::shutdown()
    {
        m_meshCache.clear();
    }

    void MeshFactory::createMesh(MeshTypes type, Rhi::Rhi* rhi)
    {
        switch (type)
        {
            case MeshTypes::Quad:
            {
                createQuadMesh(type, rhi);
                break;
            }
        }
    }

    std::shared_ptr<Mesh> MeshFactory::getMesh(MeshTypes type)
    {
        auto iterator{ m_meshCache.find(type) };
        return (iterator != m_meshCache.end()) ? iterator->second : nullptr;
    }

    void MeshFactory::createQuadMesh(MeshTypes type, Rhi::Rhi* rhi)
    {
        if (auto mesh{ getMesh(type) })
        {
            rhi->submitDrawData(mesh->vertices, mesh->indices, 3, 3);
            EventBus::publish(MeshCreationEvent(mesh));
        }
        else
        {
            mesh = std::make_shared<Mesh>();

            mesh->vertices = {
                { -0.5f, -0.5f, 0.0f },
                {  0.5f, -0.5f, 0.0f },
                {  0.5f,  0.5f, 0.0f },
                { -0.5f,  0.5f, 0.0f }
            };

            mesh->indices = {
                0, 1, 2,
                2, 3, 0
            };

            m_meshCache.emplace(type, mesh);
            rhi->submitDrawData(mesh->vertices, mesh->indices, 3, 3);
            EventBus::publish(MeshCreationEvent(mesh));
        }
    }
}
