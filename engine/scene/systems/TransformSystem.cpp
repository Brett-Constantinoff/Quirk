#include <glm/gtc/matrix_transform.hpp>

#include "TransformSystem.hpp"

namespace Quirk::Engine::Scene::Systems::TransformSystem
{
	void update(TransformComponent& transformComponent)
	{
		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), transformComponent.position);
		glm::mat4 rotationMatrix = transformComponent.rotation;
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), transformComponent.scale);

		transformComponent.transform = glm::mat4{ translationMatrix * rotationMatrix * scaleMatrix };
	}

	void rotate(TransformComponent& transformComponent, const glm::vec3& axis, double degrees)
	{
		glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(static_cast<float>(degrees)), axis);
		transformComponent.rotation = rotation * transformComponent.rotation;

		glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), transformComponent.position);
		glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), transformComponent.scale);

		transformComponent.transform = glm::mat4{ translationMatrix * transformComponent.rotation * scaleMatrix };
	}
}
