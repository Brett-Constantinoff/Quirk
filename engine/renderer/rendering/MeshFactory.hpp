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
		Sphere,
		Cube,
		Cylinder,
		Cone,
		Torus,
		Custom,
		Count
	};

	class MeshFactory
	{
	public:
		MeshFactory() = default;
		~MeshFactory() = default;

		static void init();
		static void shutdown();
		static std::shared_ptr<MeshComponent> createMesh(MeshTypes type, const char* path = nullptr);

	private:
		static void loadMeshesFromFile(std::shared_ptr<MeshComponent>& mesh, const char* path, bool isPrimitive);
		static bool isPrimitiveMesh(MeshTypes type);
		static std::shared_ptr<MeshComponent> getMesh(MeshTypes type);
		static std::shared_ptr<MeshComponent> createQuadMesh();
		static std::shared_ptr<MeshComponent> createPrimitiveMesh(MeshTypes type, const char* path);

	private:
		inline static std::unordered_map<MeshTypes, std::shared_ptr<MeshComponent>> m_meshCache{};
	};
}