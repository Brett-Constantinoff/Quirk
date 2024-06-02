#pragma once

#include "../../core/Defines.hpp"
#include "Settings.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Engine::Renderer::Utils
{
	struct Utils
	{
	public:
		static qUint32 mapPrimitiveToGl(QuirkPrimitives primitiveType)
		{
			switch (primitiveType)
			{
			case QuirkPrimitives::Triangles:     return GL_TRIANGLES;
			default:                             return -1;
			}
		}
	};
}
