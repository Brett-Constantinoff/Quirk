#pragma once

#include <cstdint>
#include <glad/glad.h>

#include "../Layout.hpp"

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray() = default;

		void bind() const;
		void unbind() const;
		uint32_t& getId();

		void setData(Layout& layout) const;

	private:
		uint32_t m_id{};
	};
} // namespace Quirk::Engine::Renderer::Rhi::Opengl