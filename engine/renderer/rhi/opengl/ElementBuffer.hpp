#pragma once

#include <cstdint>

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	class ElementBuffer
	{
	public:
		ElementBuffer();
		~ElementBuffer() = default;

		void bind() const;
		void unbind() const;
		uint32_t& getId();

		void setData(const void* data, uint32_t size) const;

	private:
		uint32_t m_id{};
	};
}