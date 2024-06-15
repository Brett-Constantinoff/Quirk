#pragma once

#include <memory>
#include <unordered_map>
#include "../rhi/Rhi.hpp"
#include "Mesh.hpp"

using namespace Quirk::Engine::Renderer::Rhi;

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
		static void createMesh(MeshTypes type, Rhi::Rhi* rhi);

	private:
		static std::shared_ptr<Mesh> getMesh(MeshTypes type);

		static void createQuadMesh(MeshTypes type, Rhi::Rhi* rhi);

	private:
		inline static std::unordered_map<MeshTypes, std::shared_ptr<Mesh>> m_meshCache{};
	};
}