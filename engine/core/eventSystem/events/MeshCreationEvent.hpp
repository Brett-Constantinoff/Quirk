#pragma once 

#include <memory>
#include <glm/glm.hpp>

#include "../../utils/Defines.hpp"
#include "../../renderer/rendering/Mesh.hpp"

#include "Event.hpp"

using namespace Quirk::Engine::Core::Utils;
using namespace Quirk::Engine::Renderer::Rendering;

namespace Quirk::Engine::Core::EventSystem::Events
{
    class MeshCreationEvent : public Event
    {
    public:
        MeshCreationEvent(const std::shared_ptr<Mesh>& mesh);
        std::shared_ptr<Mesh> getMesh() const;

    private:
        // doesnt need to own a mesh, just needs to know about it
        std::weak_ptr<Mesh> m_mesh{};
    };
}
