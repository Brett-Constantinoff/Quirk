#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "../rhi/Shader.hpp"

using namespace Quirk::Engine::Renderer::Rhi;

namespace Quirk::Engine::Renderer::Rendering
{
	enum class MaterialType
	{
		None,
		Basic2D
	};

	class ShaderManager
	{
	public:
		ShaderManager() = default;
		~ShaderManager() = default;

		static void createMaterials();
		static std::unique_ptr<Shader>& getShader(MaterialType type) { return m_shaders[type]; }

	private:
		static void createMaterial(const std::string& filePath, MaterialType type);
		static void createOpenglShader(const std::string& filePath);

	private:
		inline static std::unordered_map<MaterialType, std::unique_ptr<Shader>> m_shaders{};
	};
}