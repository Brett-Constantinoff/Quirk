#pragma once

#include <cstdint>
#include <vector>

#include "../../scene/components/MeshComponent.hpp"
#include "VertexAttribute.hpp"

using namespace Quirk::Engine::Scene::Components;

namespace Quirk::Engine::Renderer::Rhi
{
	class Layout
	{
    public:
        Layout(const MeshComponent& meshComponent, const std::vector<VertexAttribute>& attribs);
        virtual ~Layout() = default;

        virtual std::vector<VertexAttribute>& getAttributes() = 0;

        virtual const void* getVertexData() const = 0;
        virtual uint32_t getVertexDataSize() const = 0;

        virtual const void* getNormalData() const = 0;
        virtual uint32_t getNormalDataSize() const = 0;

        virtual const void* getIndexData() const = 0;
        virtual uint32_t getIndexDataSize() const = 0;

    protected:
        MeshComponent m_meshComponent;
        std::vector<VertexAttribute> m_attributes;
	};
} // namespace Quirk::Engine::Renderer::Rhi