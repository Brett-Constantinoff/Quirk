#pragma once

namespace Quirk::Engine::Renderer::Utils
{
	// Uniform names in shaders, these need to match any uniform 
	// name declared in the shaders
	inline const char* transformUniformName{ "uTransform" };
	inline const char* diffuseUniformName{ "uDiffuse" };
	inline const char* projectionUniformName{ "uProjection" };
	inline const char* viewUniformName{ "uView" };
} // namespace Quirk::Engine::Renderer::Utils