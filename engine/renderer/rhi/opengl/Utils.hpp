#include <glad/glad.h>
#include <spdlog/spdlog.h>

#include "../../../core/utils/Defines.hpp"
#include "../../utils/Settings.hpp"

using namespace Quirk::Engine::Core::Utils;
using namespace Quirk::Engine::Renderer::Utils;

namespace Quirk::Engine::Renderer::Rhi
{
    static qUint32 mapPrimitiveToGl(QuirkPrimitives primitiveType)
    {
        switch (primitiveType)
        {
        case QuirkPrimitives::Triangles:
            return GL_TRIANGLES;
        default:
            return static_cast<qUint32>(-1);
        }
    }

	static void debugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, 
		GLchar const* message, void const* user_param)
	{
		auto const srcStr = [source]() 
		{
			switch (source)
			{
				case GL_DEBUG_SOURCE_API: 
					return "API";
				case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
					return "WINDOW SYSTEM";
				case GL_DEBUG_SOURCE_SHADER_COMPILER: 
					return "SHADER COMPILER";
				case GL_DEBUG_SOURCE_THIRD_PARTY: 
					return "THIRD PARTY";
				case GL_DEBUG_SOURCE_APPLICATION: 
					return "APPLICATION";
				case GL_DEBUG_SOURCE_OTHER: 
					return "OTHER";
			}
		}();

		auto const typeStr = [type]() 
		{
			switch (type)
			{
				case GL_DEBUG_TYPE_ERROR: 
					return "ERROR";
				case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: 
					return "DEPRECATED_BEHAVIOR";
				case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: 
					return "UNDEFINED_BEHAVIOR";
				case GL_DEBUG_TYPE_PORTABILITY: 
					return "PORTABILITY";
				case GL_DEBUG_TYPE_PERFORMANCE: 
					return "PERFORMANCE";
				case GL_DEBUG_TYPE_MARKER: 
					return "MARKER";
				case GL_DEBUG_TYPE_OTHER:
					return "OTHER";
			}
		}();

		auto const severityStr = [severity]() 
		{
			switch (severity) 
			{
				case GL_DEBUG_SEVERITY_LOW: 
					return "LOW";
				case GL_DEBUG_SEVERITY_MEDIUM:
					return "MEDIUM";
				case GL_DEBUG_SEVERITY_HIGH: 
					return "HIGH";
			}
		}();

#ifdef DEBUG
		switch (severity)
		{
		case GL_DEBUG_SEVERITY_LOW:
			spdlog::warn("{}, {}, {}, {}: {}", srcStr, typeStr, severityStr, id, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			spdlog::error("{}, {}, {}, {}: {}", srcStr, typeStr, severityStr, id, message);
			break;
		case GL_DEBUG_SEVERITY_HIGH:
			spdlog::critical("{}, {}, {}, {}: {}", srcStr, typeStr, severityStr, id, message);
			break;
		default:
			spdlog::debug("{}, {}, {}, {}: {}", srcStr, typeStr, severityStr, id, message);
			break;
		}
#else
		if (severity == GL_DEBUG_SEVERITY_MEDIUM || severity == GL_DEBUG_SEVERITY_HIGH)
		{
			switch (severity)
			{
			case GL_DEBUG_SEVERITY_MEDIUM:
				spdlog::error("{}, {}, {}, {}: {}", srcStr, typeStr, severityStr, id, message);
				break;
			case GL_DEBUG_SEVERITY_HIGH:
				spdlog::critical("{}, {}, {}, {}: {}", srcStr, typeStr, severityStr, id, message);
				break;
			}
		}
#endif
	}
}
