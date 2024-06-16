#pragma once

namespace Quirk::Engine::Renderer::Rhi
{
	class Shader
	{
	public:
		Shader() = default;
		virtual ~Shader() = default;

		virtual uint32_t getId() = 0;
		virtual void use() = 0;
		virtual void disuse() = 0;
	};
}