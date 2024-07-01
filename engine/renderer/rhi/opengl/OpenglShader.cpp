#include <spdlog/spdlog.h>

#include "../../../core/utils/Utils.hpp"

#include "OpenglShader.hpp"

namespace Quirk::Engine::Renderer::Rhi::Opengl
{
    OpenglShader::OpenglShader(const std::string& filepath)
    {
        ShaderSource source{};

        m_id = glCreateProgram();

        parseShader(filepath, source);
        uint32_t vShader = compileShader(filepath, source.vertexSource, GL_VERTEX_SHADER);
        uint32_t fShader = compileShader(filepath, source.fragmentSource, GL_FRAGMENT_SHADER);

        glAttachShader(m_id, vShader);
        glAttachShader(m_id, fShader);

        glLinkProgram(m_id);

        glValidateProgram(m_id);
        glDeleteShader(vShader);
        glDeleteShader(fShader);
    }

    OpenglShader::~OpenglShader()
    {
        glDeleteProgram(m_id);
    }

    void OpenglShader::use()
    {
        glUseProgram(m_id);
    }

    void OpenglShader::disuse()
    {
		glUseProgram(0);
	}

    void OpenglShader::setVec3(const char* name, const glm::vec3& value)
    {
        glUniform3fv(glGetUniformLocation(m_id, name), 1, &value[0]);
    }

    void OpenglShader::setMat4(const char* name, const glm::mat4& matrix)
    {
		glUniformMatrix4fv(glGetUniformLocation(m_id, name), 1, GL_FALSE, &matrix[0][0]);
    }

    uint32_t OpenglShader::getId()
    {
        return m_id;
    }

    uint32_t OpenglShader::compileShader(const std::string& filepath, const std::string& source, uint32_t type)
    {
        const char* src{ source.c_str() };

        uint32_t shadermID{ static_cast<uint32_t>(glCreateShader(type)) };

        glShaderSource(shadermID, 1, &src, nullptr);

        glCompileShader(shadermID);
        
        int32_t success{};
        GLchar infoLog[512];
        glGetShaderiv(shadermID, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shadermID, 512, NULL, infoLog);
            quirkExit(std::string{ "Cannot compile shader from: " + filepath + " " + infoLog });
        }
        return shadermID;
    }

    void OpenglShader::parseShader(const std::string& filepath, ShaderSource& source)
    {
        enum class ShaderType
        {
            NONE = -1, VERTEX = 0, FRAGMENT = 1
        };

        ShaderType type = ShaderType::NONE;
        std::ifstream stream(filepath);
        if (!stream)
            quirkExit(std::string{ "Cannot find shader from: " + filepath });

        std::string line{};
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
        source.vertexSource = ss[0].str();
        source.fragmentSource = ss[1].str();
    }
}

