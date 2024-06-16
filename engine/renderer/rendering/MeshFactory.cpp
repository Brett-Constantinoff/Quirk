#include "MeshFactory.hpp"

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

    std::shared_ptr<MeshComponent> MeshFactory::createMesh(MeshTypes type, Rhi::Rhi* rhi)
    {
        switch (type)
        {
            case MeshTypes::Quad:
                return createQuadMesh(type, rhi);
        }
    }

    std::shared_ptr<MeshComponent> MeshFactory::getMesh(MeshTypes type)
    {
        auto iterator{ m_meshCache.find(type) };
        return (iterator != m_meshCache.end()) ? iterator->second : nullptr;
    }

    std::shared_ptr<MeshComponent> MeshFactory::createQuadMesh(MeshTypes type, Rhi::Rhi* rhi)
    {
        if (auto mesh{ getMesh(type) })
        {
            rhi->submitDrawData(mesh->vertices, mesh->indices, 3, 3);
            return mesh;
        }
        else
        {
            mesh = std::make_shared<MeshComponent>();

            mesh->vertices = {
                { -0.5f, -0.5f, 0.0f },
                {  0.5f, -0.5f, 0.0f },
                {  0.5f,  0.5f, 0.0f },
                { -0.5f,  0.5f, 0.0f }
            };
            mesh->vertexCount = static_cast<uint32_t>(mesh->vertices.size());

            mesh->indices = {
                0, 1, 2,
                2, 3, 0
            };
            mesh->indexCount = static_cast<uint32_t>(mesh->indices.size());

            m_meshCache.emplace(type, mesh);
            rhi->submitDrawData(mesh->vertices, mesh->indices, 3, 3);

            return mesh;
        }
        
    }
}
