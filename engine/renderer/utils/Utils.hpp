#pragma once

namespace Quirk::Engine::Renderer::Utils
{
	// Uniform names in shaders, these need to match any uniform 
	// name declared in the shaders
	static const char* transformUniformName{ "uTransform" };
	static const char* diffuseUniformName{ "uDiffuse" };
	static const char* projectionUniformName{ "uProjection" };
	static const char* viewUniformName{ "uView" };
}