#include <spdlog/spdlog.h>

#include "Shader.hpp"
#include "../../core/Utils.hpp"

using namespace Quirk::Engine::Core;

namespace Quirk::Engine::Renderer::Rendering::Shaders
{
    Shader::Shader(const std::string& filepath) :
        m_shaderFile{ filepath }
    {
        m_ID = glCreateProgram();

        parseShader();
        uint32_t vShader = compileShader(m_shaderSource.vertexSource, GL_VERTEX_SHADER);
        uint32_t fShader = compileShader(m_shaderSource.fragmentSource, GL_FRAGMENT_SHADER);

        glAttachShader(m_ID, vShader);
        glAttachShader(m_ID, fShader);
        glLinkProgram(m_ID);
        glValidateProgram(m_ID);
        glDeleteShader(vShader);
        glDeleteShader(fShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_ID);
    }

    void Shader::use(void)
    {
        glUseProgram(m_ID);
    }

    void Shader::disuse(void)
    {
        glUseProgram(0);
    }

    int32_t Shader::getId(void) const
    {
        return m_ID;
    }

    int32_t Shader::compileShader(const std::string& source, int32_t type)
    {
        const char* src = source.c_str();

        int32_t shadermID = glCreateShader(type);
        glShaderSource(shadermID, 1, &src, nullptr);
        glCompileShader(shadermID);

        int32_t success;
        GLchar infoLog[512];
        glGetShaderiv(shadermID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shadermID, 512, NULL, infoLog);
            Utils::Exit(std::string{ "Cannot compile shader from: " + m_shaderFile + " " + infoLog });
        }
        return shadermID;
    }

    void Shader::parseShader()
    {
        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        ShaderType type = ShaderType::NONE;
        std::ifstream stream(m_shaderFile);
        if (!stream)
            Utils::Exit(std::string{ "Cannot find shader from: " + m_shaderFile});

        std::string line;
        std::stringstream ss[2];

        while (getline(stream, line))
        {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertexShader") != std::string::npos)
                    type = ShaderType::VERTEX;

                else if (line.find("fragmentShader") != std::string::npos)
                    type = ShaderType::FRAGMENT;

            }
            else
                ss[(int32_t)type] << line << '\n';
        }
        m_shaderSource.vertexSource = ss[0].str();
        m_shaderSource.fragmentSource = ss[1].str();
    }

    int32_t Shader::getUniform(const std::string& name)
    {
        // uniform has been located, return from cache
        if (m_uniformCache.find(name.c_str()) != m_uniformCache.end())
            return m_uniformCache[name.c_str()];

        // add new uniform to the not found cache with print value 0
        m_uniformNotFoundCache[name.c_str()] = 0;

        int32_t location = glGetUniformLocation(m_ID, name.c_str());

        // uniform not found
        if (location == -1)
        {
            // only print this message once per uniform, otherwise endless logs will be printed
            if (m_uniformNotFoundCache[name.c_str()] == 0)
            {
                spdlog::warn(std::string{ "Cannot compile shader from: " + name });
                m_uniformNotFoundCache[name.c_str()] = 1;
            }
        }

        // uniform found correctly, add it to location cache
        m_uniformCache[name.c_str()] = location;
        return location;
    }

    void Shader::setVec4(const std::string& name, const glm::vec4& uniform)
    {
        int32_t location = getUniform(name);
        if (location != -1)
            glUniform4fv(location, 1, &uniform[0]);
    }

    void Shader::setVec3(const std::string& name, const glm::vec3& uniform)
    {
        int32_t location = getUniform(name);
        if (location != -1)
            glUniform3fv(location, 1, &uniform[0]);
    }

    void Shader::setMat4(const std::string& name, const glm::mat4& uniform)
    {
        int32_t location = getUniform(name);
        if (location != -1)
            glUniformMatrix4fv(location, 1, GL_FALSE, &uniform[0][0]);
    }

    void Shader::setInt(const std::string& name, int32_t uniform)
    {
        int32_t location = getUniform(name);
        if (location != -1)
            glUniform1i(location, uniform);

    }

    void Shader::setFloat(const std::string& name, float uniform)
    {
        int32_t location = getUniform(name);
        if (location != -1)
            glUniform1f(location, uniform);
    }
}

