#pragma once

namespace Quirk::Engine::Scene
{
    class Actor
    {
    public:
        inline Actor(entt::registry& registry)
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

    private:
        entt::registry& m_registry;
		entt::entity m_entity;
    };
}
