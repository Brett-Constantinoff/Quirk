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
		
		// contains basic lighting implementation, some values are hardcoded
		// dont use for serious rendering
		Basic,
	};

	class ShaderManager
	{
	public:
		ShaderManager() = default;
		~ShaderManager() = default;

		static void init();
		static void shutdown();
		[[nodiscard]] static uint32_t getMaterialId(MaterialType type);
		[[nodiscard]] static std::unique_ptr<Shader>& getMaterial(uint32_t id);

	private:
		static void createMaterial(const std::string& filePath, MaterialType type);
		static void createOpenglMaterial(const std::string& filePath);

	private:
		// leaving these as heap allocated since they need to be determined based on our 
		// rhi
		inline static std::unordered_map<MaterialType, std::unique_ptr<Shader>> m_shaders{};
	};
}