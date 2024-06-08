#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "../Shader.hpp"

#include "../../../core/utils/Defines.hpp"

using namespace Quirk::Engine::Core::Utils;

namespace Quirk::Engine::Renderer::Rhi
{
    struct ShaderSource
    {
        std::string vertexSource{};
        std::string fragmentSource{};
    };

    class OpenglShader : public Shader
    {
    public:
        OpenglShader(const std::string& filepath);
        virtual ~OpenglShader() override;

        virtual void use() override;
        virtual void disuse() override;
        int32_t getId(void) const;

    private:
        void parseShader(const std::string& filepath, ShaderSource& source);
        int32_t compileShader(const std::string& filepath, const std::string& source, int32_t type);

    private:
        int32_t m_id{};
    };
}