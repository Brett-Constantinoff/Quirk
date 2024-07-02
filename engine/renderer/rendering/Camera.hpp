#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

namespace Quirk::Engine::Renderer::Rendering
{
    class Camera
    {
    public:
        Camera();
        ~Camera() = default;

        void move(float dt);
        glm::mat4& getView();
        glm::vec3& getPos();
        glm::vec3& getFront();
        float getNear() const;
        float getFar() const;
        float getZoom() const;

    private:
        void updateVectors();

    private:
        glm::vec3 m_pos{0.0f, 0.0f, 5.0f};
        glm::vec3 m_front{0.0f, 0.0f, -1.0f};
        glm::vec3 m_worldUp{0.0f, 1.0f, 0.0f};
        glm::vec3 m_up{};
        glm::vec3 m_right{};
        float m_yaw{-90.0f};
        float m_pitch{0.0f};
        float m_speed{};
        float m_zoom{};
        float m_sensitivity{};
        float m_near{0.1f};
        float m_far{100.0f};
        glm::mat4 m_view{};
    };
} // namespace Quirk::Engine::Renderer::Rendering