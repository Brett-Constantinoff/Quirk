#pragma once

#include "../../core/utils/Defines.hpp"
#include "Settings.hpp"

using namespace Quirk::Engine::Core::Utils;

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
