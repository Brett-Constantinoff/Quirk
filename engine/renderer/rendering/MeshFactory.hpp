#pragma once

#include <memory>
#include <unordered_map>

#include "Mesh.hpp"

namespace Quirk::Engine::Renderer::Rendering
{
	enum class MeshTypes
	{
		None,
		Quad,

		Count
	};

	class MeshFactory
	{
	public:
		MeshFactory() = default;
		~MeshFactory() = default;

		static void init();
		static void shutdown();
		static std::shared_ptr<Mesh> getMesh(MeshTypes type);

	private:
		static std::shared_ptr<Mesh> createMesh(MeshTypes type);

	private:
		inline static std::unordered_map<MeshTypes, std::shared_ptr<Mesh>> m_meshCache{};
	};
}