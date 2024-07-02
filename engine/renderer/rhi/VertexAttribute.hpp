#pragma once

#include <cstdint>

#include "../utils/Settings.hpp"

using namespace Quirk::Engine::Renderer::Utils;

namespace Quirk::Engine::Renderer::Rhi
{
    struct VertexAttribute {
        uint32_t index{};
        int32_t size{};
        QuirkTypes type{};
        bool normalized{};
        std::size_t stride{};
        const void* pointer{};
    };
} // namespace Quirk::Engine::Renderer::Rhi