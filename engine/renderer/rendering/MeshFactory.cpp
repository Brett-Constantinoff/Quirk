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

	std::shared_ptr<Mesh> MeshFactory::getMesh(MeshTypes type)
	{
		auto iterator{ m_meshCache.find(type) };

		if (iterator != m_meshCache.end())
			return iterator->second;

		auto mesh{ createMesh(type) };

		m_meshCache[type] = mesh;

		return mesh;
	}

	std::shared_ptr<Mesh> MeshFactory::createMesh(MeshTypes type)
	{
		switch (type)
		{
			case MeshTypes::Quad:
			{
				auto mesh = std::make_shared<Mesh>();

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

				return mesh;
			}
			default:
				return nullptr;
		}
	}
}