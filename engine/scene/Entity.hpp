#pragma once

#include <uuid.h>
#include <entt/entt.hpp>

namespace Quirk::Engine::Scene
{
    class Entity
    {
    public:
        inline Entity(entt::registry& registry)
            : m_registry{ registry },
            m_entity{ m_registry.create() }
        {
        }

        template<typename T, typename... Args>
        inline constexpr T& addComponent(Args&&... args)
        {
            return m_registry.emplace<T>(m_entity, std::forward<Args>(args)...);
        }

        template<typename T>
        inline constexpr T& getComponent()
        {
            return m_registry.get<T>(m_entity);
        }

        template<typename T>
        inline constexpr bool hasComponent() const
        {
            return m_registry.any_of<T>(m_entity);
        }

        template<typename T>
        inline constexpr void removeComponent()
        {
            m_registry.remove<T>(m_entity);
        }

        [[nodiscard]] inline constexpr entt::entity getHandle() const
        {
            return m_entity;
        }

        [[nodiscard]] inline constexpr bool isDrawable() const
		{
			return m_drawable;
		}

        inline constexpr void setDrawable(bool drawable)
        {
            m_drawable = drawable;
        }

        [[nodiscard]] inline constexpr std::wstring getId()
        {
            const auto& nameComponent{ getComponent<Components::NameComponent>() };
            return nameComponent.id;
        }

    private:
        entt::registry& m_registry;
		entt::entity m_entity;
        bool m_drawable{ false };
    };
}
