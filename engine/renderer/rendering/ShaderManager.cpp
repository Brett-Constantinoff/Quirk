#pragma once

#include "../utils/Context.hpp"

#include "../rhi/opengl/OpenglShader.hpp"

#include "ShaderManger.hpp"

using namespace Quirk::Engine::Renderer::Utils;

using RenderApi = Quirk::Engine::Core::Utils::RenderApi;

namespace Quirk::Engine::Renderer::Rendering
{
	void ShaderManager::init()
	{
		createMaterial("../engine/resources/shaders/basicShader.hlsl", MaterialType::Basic2D);
	}

	void ShaderManager::shutdown()
	{
		m_shaders.clear();
	}

	void ShaderManager::createMaterial(const std::string& filePath, MaterialType type)
	{
		switch (Context::renderApi)
		{
			case RenderApi::OpenGL:
				createOpenglShader(filePath);
				break;
		}
	}

	void ShaderManager::createOpenglShader(const std::string& filePath)
	{
		m_shaders[MaterialType::Basic2D] = std::make_unique<OpenglShader>(filePath);
	}
}