#pragma once

#include <memory>
#include <unordered_map>
#include "../rhi/Rhi.hpp"
#include "../../scene/components/MeshComponent.hpp"

using namespace Quirk::Engine::Renderer::Rhi;
using namespace Quirk::Engine::Scene::Components;

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
		static std::shared_ptr<MeshComponent> createMesh(MeshTypes type, Rhi::Rhi* rhi);

	private:
		static std::shared_ptr<MeshComponent> getMesh(MeshTypes type);

		static std::shared_ptr<MeshComponent> createQuadMesh(MeshTypes type, Rhi::Rhi* rhi);

	private:
		inline static std::unordered_map<MeshTypes, std::shared_ptr<MeshComponent>> m_meshCache{};
	};
}