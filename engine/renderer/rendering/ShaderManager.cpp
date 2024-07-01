#pragma once

#include "../../core/utils/Utils.hpp"
#include "../utils/Context.hpp"
#include "../rhi/opengl/OpenglShader.hpp"

#include "ShaderManger.hpp"

using namespace Quirk::Engine::Renderer::Utils;
using namespace Quirk::Engine::Core::Utils;

using RenderApi = Quirk::Engine::Core::Utils::RenderApi;

namespace Quirk::Engine::Renderer::Rendering
{
	void ShaderManager::init()
	{
		createMaterial(basicShaderPath, MaterialType::Basic2D);
	}

	void ShaderManager::shutdown()
	{
		m_shaders.clear();
	}

	uint32_t ShaderManager::getMaterialId(MaterialType type)
	{
		return m_shaders[type]->getId();
	}

	std::unique_ptr<Shader>& ShaderManager::getMaterial(uint32_t id)
	{
		for (auto& shader : m_shaders)
		{
			if (shader.second->getId() == id)
				return shader.second;
		}
		return m_shaders[MaterialType::Basic2D];
	}
	
	void ShaderManager::createMaterial(const std::string& filePath, MaterialType type)
	{
		switch (Context::renderApi)
		{
			case RenderApi::OpenGL:
				createOpenglMaterial(filePath);
				break;
		}
	}

	void ShaderManager::createOpenglMaterial(const std::string& filePath)
	{
		m_shaders[MaterialType::Basic2D] = std::make_unique<OpenglShader>(filePath);
	}
}