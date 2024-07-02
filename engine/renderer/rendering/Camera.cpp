#include "Camera.hpp"

namespace Quirk::Engine::Renderer::Rendering
{
    Camera::Camera()
    {
        updateVectors();
    };

    void Camera::move(float dt)
    {
    }

    glm::mat4& Camera::getView()
    {
        m_view = glm::lookAt(m_pos, m_pos + m_front, m_up);
        return m_view;
    }

    glm::vec3& Camera::getPos()
    {
        return m_pos;
    }

    glm::vec3& Camera::getFront()
    {
        return m_front;
    }

    float Camera::getNear() const
    {
        return m_near;
    }

    float Camera::getFar() const
    {
        return m_far;
    }

    float Camera::getZoom() const
    {
        return m_zoom;
    }

    void Camera::updateVectors()
    {
        glm::vec3 front{};
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

        m_front = glm::normalize(front);
        m_right = glm::normalize(glm::cross(m_front, m_worldUp));
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }
} // namespace Quirk::Engine::Renderer::Rendering