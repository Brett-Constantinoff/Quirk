#pragma once

#include "../../../scene/components/MeshComponent.hpp"

#include "../VertexAttribute.hpp"
#include "../Layout.hpp"

using namespace Quirk::Engine::Scene::Components;

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
	class OpenglLayout : public Layout
	{
	public:
		OpenglLayout(const MeshComponent& meshComponent, const std::vector<VertexAttribute>& attribs);
		~OpenglLayout() override;

		std::vector<VertexAttribute>& getAttributes() override;

		const void* getVertexData() const override;
		uint32_t getVertexDataSize() const override;

		const void* getNormalData() const override;
		uint32_t getNormalDataSize() const override;

		const void* getIndexData() const override;
		uint32_t getIndexDataSize() const override;
	};
} // namespace Quirk::Engine::Renderer::Rhi::Opengl