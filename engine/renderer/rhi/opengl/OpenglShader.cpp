#include <spdlog/spdlog.h>

#include "OpenglShader.hpp"

#include "../../../core/utils/Utils.hpp"

namespace Quirk::Engine::Renderer::Rhi
{
    OpenglShader::OpenglShader(const std::string& filepath)
    {
        ShaderSource source{};

        m_id = glCreateProgram();

        parseShader(filepath, source);
        qUint32 vShader = compileShader(filepath, source.vertexSource, GL_VERTEX_SHADER);
        qUint32 fShader = compileShader(filepath, source.fragmentSource, GL_FRAGMENT_SHADER);

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

    qInt32 OpenglShader::getId(void) const
    {
        return m_id;
    }

    qInt32 OpenglShader::compileShader(const std::string& filepath, const std::string& source, qInt32 type)
    {
        const char* src{ source.c_str() };

        qInt32 shadermID{ static_cast<qInt32>(glCreateShader(type)) };

        glShaderSource(shadermID, 1, &src, nullptr);

        glCompileShader(shadermID);
        
        qInt32 success{};
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
