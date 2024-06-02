#pragma once

#include "../../core/Defines.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	class ElementBuffer
	{
	public:
		ElementBuffer();
		~ElementBuffer() = default;

		void bind() const;
		void unbind() const;
		qUint32& getId();

		void setData(const void* data, qUint32 size) const;

	private:
		qUint32 m_id{};
	};
}